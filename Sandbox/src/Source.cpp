#include <Leviathan.h>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <memory>
#include "Player.h"
#include "World/WorldObject.h"

#define LEVIATHAN_DEBUG_SHADER

using namespace Leviathan::Graphics;
using namespace Leviathan::Graphics::Buffers;
using namespace Leviathan::Input;
using namespace Leviathan;
using namespace Leviathan::Events;

using Leviathan::Window;

class Game : public Application {
public:
	WorldObject* wo1;
	WorldObject* wo2;
	WorldObject* wo3;
	WorldObject* wo4;
	WorldObject* wo5;

	WorldObject* wo0;
	WorldObject* pl1;
	WorldObject* pl2;
	WorldObject* pl3;
	WorldObject* pl4;

	std::shared_ptr<Camera> cam;

	FrameBuffer* fb;
	Timestep last_frametime;
	std::shared_ptr<Player> player;

	double timestamp;
	Game() : Application{1080, 720, "Dat shit that is important", WindowMode::WINDOWED} {
		FileManager::RegisterDirectory("default", FileManager::GetWorkingDir());
		FileManager::RegisterDirectory("shaders", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\shaders");
		FileManager::RegisterDirectory("textures", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\textures");
		FileManager::RegisterDirectory("models", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\models");
		FileManager::RegisterDirectory("images", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\images");

		std::shared_ptr<Mesh> mesh = std::make_shared<ModelMesh>("models", "ape2.obj");
		std::shared_ptr<Mesh> mesh2 = std::make_shared<ModelMesh>("models", "wall.obj");
		MeshStorage::AddMesh("ape", mesh);
		MeshStorage::AddMesh("wall", mesh2);
		//Mesh::AddMesh("cube", "models", "cube_t.obj");
		//Mesh::AddMesh("awp", "models", "AWP_Dragon_Lore.obj");
		ShaderProgram::AddShader("block", "shaders", "block.frag", "block.vert");
		ShaderProgram::AddShader("toon", "shaders", "toon.frag", "toon.vert");
		ShaderProgram::AddShader("wave", "shaders", "wave.frag", "wave.vert");
		ShaderProgram::AddShader("proc", "shaders", "proc.frag", "proc.vert");
		ShaderProgram::AddShader("multitex", "shaders", "multitex.frag", "multitex.vert");
		ShaderProgram::AddShader("normalvis", "shaders", "normalvis.frag", "normalvis.vert", "normalvis.geo");
		ShaderProgram::AddShader("scdistort", "shaders", "scdistort.frag", "scdistort.vert");
		ShaderProgram::AddShader("sccolinv", "shaders", "sccolinv.frag", "sccolinv.vert");
		ShaderProgram::AddShader("scgrain", "shaders", "scgrain.frag", "scgrain.vert");
		ShaderProgram::AddShader("scblur", "shaders", "scblur.frag", "scblur.vert");


		TextureReference tref = std::make_shared<Texture2D>("textures", "awp_color.png", false);
		TextureReference tref2 = std::make_shared<Texture2D>("textures", "atlas.png", false);
		TextureReference tref3 = std::make_shared<Texture2D>("textures", "laminate1.png", false);
		TextureReference tref4 = std::make_shared<Texture2D>("textures", "laminate2.png", false);
		TextureStorage::AddTexture("default", tref);
		TextureStorage::AddTexture("atlas", tref2);
		TextureStorage::AddTexture("laminate1", tref3);
		TextureStorage::AddTexture("laminate2", tref4);

		cam = std::make_shared<Camera>(glm::vec3(0, 0.0, 2.0), glm::vec3(0.0, 90.0, 0.0));

		DepthBuffer::Enable();
		DepthBuffer::SetDepthFunction(DepthFunc::LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		std::shared_ptr<Leviathan::Image> im = Leviathan::Image::Load("default", "logo.png");
		std::shared_ptr<Leviathan::Window> window = this->GetWindow().lock();
		
		window->SetWindowIcon(im);
		window->SetVSync(true);

		this->last_frametime = 0.0;
		//cam = Camera::GetPrimary();
		this->player = std::make_shared<Player>();
		fb = new FrameBuffer(1080, 720, "text_fb");
		
		//Backwall
		wo0 = new WorldObject();
		wo0->setMesh("wall");
		wo0->setShader("block");
		wo0->transform.Scale(glm::vec3(20.0f, 20.0f, 20.0f));
		wo0->transform.Translate(glm::vec3(0.0f, -20.0f, -10.0f));
		wo0->transform.Rotate(glm::vec3(0.0f, 90.0f, 0.0f));

		wo1 = new WorldObject();
		wo1->setMesh("ape");
		wo1->setShader("toon");
		wo1->transform.Translate(glm::vec3(0.0f, 0.0f, 0.0f));

		wo2 = new WorldObject();
		wo2->setMesh("ape");
		wo2->setShader("wave");
		wo2->transform.Translate(glm::vec3(5.0f, 0.0f, 0.0f));

		wo3 = new WorldObject();
		wo3->setMesh("ape");
		wo3->setShader("proc");
		wo3->transform.Translate(glm::vec3(10.0f, 0.0f, 0.0f));

		wo4 = new WorldObject();
		wo4->setMesh("ape");
		wo4->setShader("multitex");
		wo4->getTexture()->SetTexture("laminate1", 0);
		wo4->getTexture()->SetTexture("laminate2", 1);
		wo4->transform.Translate(glm::vec3(15.0f, 0.0f, 0.0f));

		wo5 = new WorldObject();
		wo5->setMesh("ape");
		wo5->setShader("normalvis");
		wo5->transform.Translate(glm::vec3(20.0f, 0.0f, 0.0f));

		pl1 = new WorldObject();
		pl1->setMesh("wall");
		pl1->setShader("scdistort");
		pl1->getTexture()->SetTexture("text_fb", 0);
		pl1->transform.Scale(glm::vec3(0.75f, 0.75f, 0.75f));
		pl1->transform.Translate(glm::vec3(0.0f, 0.0f, 10.0f));
		pl1->transform.Rotate(glm::vec3(0.0f, 90.0f, 0.0f));

		pl2 = new WorldObject();
		pl2->setMesh("wall");
		pl2->setShader("sccolinv");
		pl2->getTexture()->SetTexture("text_fb", 0);
		pl2->transform.Scale(glm::vec3(0.75f, 0.75f, 0.75f));
		pl2->transform.Translate(glm::vec3(5.0f, 0.0f, 10.0f));
		pl2->transform.Rotate(glm::vec3(0.0f, 90.0f, 0.0f));

		pl3 = new WorldObject();
		pl3->setMesh("wall");
		pl3->setShader("scgrain");
		pl3->getTexture()->SetTexture("text_fb", 0);
		pl3->transform.Scale(glm::vec3(0.75f, 0.75f, 0.75f));
		pl3->transform.Translate(glm::vec3(10.0f, 0.0f, 10.0f));
		pl3->transform.Rotate(glm::vec3(0.0f, 90.0f, 0.0f));

		pl4 = new WorldObject();
		pl4->setMesh("wall");
		pl4->setShader("scblur");
		pl4->getTexture()->SetTexture("text_fb", 0);
		pl4->transform.Scale(glm::vec3(0.75f, 0.75f, 0.75f));
		pl4->transform.Translate(glm::vec3(15.0f, 0.0f, 10.0f));
		pl4->transform.Rotate(glm::vec3(0.0f, 90.0f, 0.0f));

		timestamp = 0.0;
	}
	~Game() = default;

	 void OnEvent(Event* event) override {
		 std::string ss = event->ToString();
		 switch (event->GetCategory()) {
		 case EventCategory::WindowEvent:
			 this->OnWindowEvent(event);
			 break;
		 case EventCategory::MouseEvent:
			 this->OnMouseEvent(event);
			 break;
		}
	 }

	 void CheckFps() {
		 double time = glfwGetTime();
		 double frame_delta = time - timestamp;
		 double fps = round(1.0 / frame_delta);

		 this->last_frametime.SetTimestep(frame_delta);
		 std::shared_ptr<Leviathan::Window> window = this->GetWindow().lock();
		 std::shared_ptr<Camera> camera = this->player->GetCamera().lock();
		 glm::vec3 position = camera->GetPosition();
		 glm::vec3 rotation = camera->GetRotation();
		 glm::vec3 velocity = player->GetVelocity(); 
		 if (window) {
			 std::stringstream ss;
			ss << "\t Pos[X:" << position.x << "| Y:" << position.y << "| Z:" << position.z <<"]\t"
				 << "\t Rot[X:" << rotation.x << "| Y:" << rotation.y << "| Z:" << rotation.z << "]"
				<< "\t Vel[X:" << velocity.x << "| Y:" << velocity.y << "| Z:" << velocity.z << "]";
			 window->SetTitle(ss.str());
		 }
		 this->timestamp = time;
	 }

	 void OnMouseEvent(Event* ev) {
		 std::shared_ptr<Mouse> mouse = this->GetMouse().lock();
		 if (mouse) {
			 switch (ev->GetEventType()) {
			 case EventType::MouseMove:
			 {
				 if (mouse->GetMouseMode() != MouseMode::CENTERED) {
					 return;
				 }
				 std::shared_ptr<Camera> camera = player->GetCamera().lock();
				 if (camera) {
					 MouseMoveEvent* event = (MouseMoveEvent*)ev;
					 double dx, dy;
					 event->GetDelta(&dx, &dy);
					 this->player->Rotate(glm::vec3((float)dy, (float)-dx, 0.0f));
					 glm::vec3 cam_angle = camera->GetRotation();
				 }
			 } break;
			 case EventType::MouseWheel:
			 {
				 MouseWheelEvent* event = (MouseWheelEvent*)ev;
				 double dx, dy;
				 event->GetScroll(&dx, &dy);
			 } break;
			 }
		 }
		 
	 }

	 float key_mult = 0.05f;
	 void CheckKeyboardKeys() {
		 std::shared_ptr<Keyboard> keyboard = this->GetKeyboard().lock();
		 if (keyboard) {
			 std::vector<KeyCode> pressed_keys;

			 keyboard->GetPressedKeys(&pressed_keys);
			 for (size_t i = 0; i < pressed_keys.size(); i++) {
				 switch (pressed_keys[i]) {
				 case KeyCode::KEY_W:
					 player->MoveForeward(this->last_frametime.GetSeconds() * key_mult);
					 break;
				 case KeyCode::KEY_S:
					 player->MoveBackward(this->last_frametime.GetSeconds() * key_mult);
					 break;
				 case KeyCode::KEY_A:
					 player->MoveLeft(this->last_frametime.GetSeconds() * key_mult);
					 break;
				 case KeyCode::KEY_D:
					 player->MoveRight(this->last_frametime.GetSeconds() * key_mult);
					 break;
				 case KeyCode::KEY_SPACE:
					 player->MoveUp(this->last_frametime.GetSeconds() * key_mult);
					 break;
				 case KeyCode::KEY_LEFT_SHIFT:
					 player->MoveDown(this->last_frametime.GetSeconds() * key_mult);
					 break;
				 case KeyCode::KEY_E:
				 {
					 std::shared_ptr<Leviathan::Window> window = this->GetWindow().lock();
					 if (window) {
						 if (window->GetCursorMode() == MouseMode::VISIBLE) {
							 window->SetCursorMode(MouseMode::CENTERED);
						 }
						 else {
							 window->SetCursorMode(MouseMode::VISIBLE);
						 }
					 }
				 }
					 break;
				 default:
					 continue;
				 }
			 }
		 }
	 }

	 void OnWindowEvent(Event* event) {
		 if (event->GetEventType() == EventType::WindowRefresh) {
			 CheckFps();
			 CheckKeyboardKeys();
			 Leviathan::Renderer::Render(*wo0, player->GetCamera());
			 Leviathan::Renderer::Render(*wo1, player->GetCamera());
			 Leviathan::Renderer::Render(*wo2, player->GetCamera());
			 Leviathan::Renderer::Render(*wo3, player->GetCamera());
			 Leviathan::Renderer::Render(*wo4, player->GetCamera());
			 Leviathan::Renderer::Render(*wo5, player->GetCamera());
			 //wo->RotateDeg(glm::vec3(this->last_frametime, 0.0f, 0.0f));

			 fb->Bind();
			 Leviathan::Renderer::Render(*wo0, cam);
			 Leviathan::Renderer::Render(*wo1, cam);
			 Leviathan::Renderer::Render(*wo2, cam);
			 Leviathan::Renderer::Render(*wo3, cam);
			 Leviathan::Renderer::Render(*wo4, cam);
			 Leviathan::Renderer::Render(*wo5, cam);
			 fb->Unbind();
			 
			 Leviathan::Renderer::Render(*pl1, player->GetCamera());
			 Leviathan::Renderer::Render(*pl2, player->GetCamera());
			 Leviathan::Renderer::Render(*pl3, player->GetCamera());
			 Leviathan::Renderer::Render(*pl4, player->GetCamera());
			 player->Update(this->last_frametime);
		 }
	 }
};

int main() {
	std::unique_ptr<Game> app = std::make_unique<Game>();
	app->Run();
	app.reset();

	return 1;
}