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
	WorldObject* wo;
	Timestep last_frametime;
	std::shared_ptr<Player> player;

	double timestamp;
	Game() : Application{1080, 720, "Minecraft", WindowMode::WINDOWED} {
		FileManager::RegisterDirectory("default", FileManager::GetWorkingDir());
		FileManager::RegisterDirectory("shaders", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\shaders");
		FileManager::RegisterDirectory("textures", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\textures");
		FileManager::RegisterDirectory("models", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\models");
		FileManager::RegisterDirectory("images", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\images");

		Mesh::AddMesh("cube", "models", "cube_t.obj");
		ShaderProgram::AddShader("block", "shaders", "block.frag", "block.vert");
		ShaderProgram::AddShader("block", "shaders", "block.frag", "block.vert");
		ShaderProgram::AddShader("grayblock", "shaders", "grayblock.frag", "grayblock.vert");
		ShaderProgram::AddShader("colblock", "shaders", "colblock.frag", "colblock.vert");
		
		DepthBuffer::Enable();
		DepthBuffer::SetDepthFunction(DepthFunc::LESS);
		std::shared_ptr<Leviathan::Image> im = Leviathan::Image::Load("default", "logo.png");
		std::shared_ptr<Leviathan::Window> window = this->GetWindow().lock();
		window->SetWindowIcon(im);
		window->SetVSync(true);

		this->last_frametime = 0.0;
		//cam = Camera::GetPrimary();
		this->player = std::make_shared<Player>();
		wo = new WorldObject();
		wo->setMesh("cube");
		wo->setShader("colblock");
		wo->setPosition(glm::vec3(5.0f, 0.0f, 0.0f));

		TextureReference tref = Texture::GetTexture("default").lock();
		if (tref != nullptr) {
			tref->SetMinMagSetting(MinMagSetting::LINEAR, MinMagSetting::LINEAR);
		}

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
		 if (ev->GetEventType() == EventType::MouseMove && mouse) {
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
				 case KeyCode::KEY_UP:
					 player->AddVelocity(glm::vec3(0.0f, 1.0f, 0.0f));
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
			 Leviathan::Renderer::Render(*wo, player->GetCamera());
			 wo->RotateDeg(glm::vec3(this->last_frametime, 0.0f, 0.0f));
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