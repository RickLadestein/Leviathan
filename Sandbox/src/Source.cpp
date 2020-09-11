#include <Leviathan.h>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <memory>
#include "Player.h"
#include "reactphysics3d/engine/Entity.h"

class WorldObject: public Drawable {
public:
	WorldObject(std::string mesh_name) {
		this->shader = "default";
		this->texture = "default";
		Initialize(mesh_name);
	}

	void Initialize(std::string mesh_name) {
		std::shared_ptr<Mesh> mesh = Mesh::GetMesh(mesh_name).lock();
		if (mesh) {
			this->vertexbuffer.BufferData(mesh->data);
		}
	}
};

class Game : public Application {
public:
	WorldObject* wo;
	Timestep last_frametime;
	//float last_frametime;
	//std::weak_ptr<Camera> cam;
	std::shared_ptr<Player> player;

	double timestamp;
	Game() : Application{1080, 720, "Minecraft", WindowMode::WINDOWED} {
		FileManager::RegisterDirectory("default", FileManager::GetWorkingDir());
		FileManager::RegisterDirectory("shaders", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\shaders");
		FileManager::RegisterDirectory("textures", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\textures");
		FileManager::RegisterDirectory("models", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\models");
		FileManager::RegisterDirectory("images", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\images");

		Mesh::AddMesh("awp", "models", "AWP_Dragon_Lore.obj");
		Mesh::AddMesh("overlay", "models", "crosshair.obj");
		ShaderProgram::AddShader("default", "shaders", "default.frag", "default.vert");
		ShaderProgram::AddShader("crosshair", "shaders", "crosshair.frag", "crosshair.vert");
		Texture::AddTexture("default", "textures", "awp_color.png", false);
		
		DepthBuffer::Enable();
		DepthBuffer::SetDepthFunction(DepthFunc::LESS);

		std::shared_ptr<leviathan::Image> im = leviathan::Image::Load("default", "logo.png");
		std::shared_ptr<Window> window = this->GetWindow().lock();
		window->SetWindowIcon(im);
		window->SetVSync(true);

		this->last_frametime = 0.0;
		//cam = Camera::GetPrimary();
		this->player = std::make_shared<Player>();
		wo = new WorldObject("awp");
		wo->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		timestamp = 0.0;
	}
	~Game() = default;

	 void OnEvent(Event* event) override {
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
		 std::shared_ptr<Window> window = this->GetWindow().lock();
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
		 if (ev->GetType() == EventType::MouseMoveEvent && mouse) {
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

	 void CheckKeyboardKeys() {
		 std::shared_ptr<Keyboard> keyboard = this->GetKeyboard().lock();
		 if (keyboard) {
			 std::vector<int> pressed_keys;
			 keyboard->GetPressedKeys(&pressed_keys);
			 for (int i = 0; i < pressed_keys.size(); i++) {
				 switch (pressed_keys[i]) {
				 case GLFW_KEY_W:
					 player->MoveForeward(this->last_frametime);
					 break;
				 case GLFW_KEY_S:
					 player->MoveBackward(this->last_frametime);
					 break;
				 case GLFW_KEY_A:
					 player->MoveLeft(this->last_frametime);
					 break;
				 case GLFW_KEY_D:
					 player->MoveRight(this->last_frametime);
					 break;
				 case GLFW_KEY_UP:
					 player->AddVelocity(glm::vec3(0.0f, 1.0f, 0.0f));
				 case GLFW_KEY_SPACE:
					 player->MoveUp(this->last_frametime);
					 break;
				 case GLFW_KEY_LEFT_SHIFT:
					 player->MoveDown(this->last_frametime);
					 break;
				 case GLFW_KEY_E:
				 {
					 std::shared_ptr<Window> window = this->GetWindow().lock();
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
		 if (event->GetType() == EventType::RefreshEvent) {
			 CheckFps();
			 CheckKeyboardKeys();
			 Renderer::Render(*wo, player->GetCamera());

			 player->Update(this->last_frametime);
		 }
	 }
};
int main() {
	std::shared_ptr<Game> app = std::make_shared<Game>();
	app->Run();
	app.reset();
	return 1;
}