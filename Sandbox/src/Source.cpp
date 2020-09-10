#include <Leviathan.h>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <memory>

class WorldObject: public Drawable {
public:
	WorldObject() {
		this->shader = "default";
		this->texture = "default";
		Initialize();
	}

	void Initialize() {
		std::shared_ptr<Mesh> mesh = Mesh::GetMesh("awp").lock();
		if (mesh) {
			this->vertexbuffer.BufferData(mesh->data);
		}
	}
};

class Game : public Application {
public:
	WorldObject* wo;
	std::weak_ptr<Camera> cam;

	double timestamp;
	Game() : Application{1080, 720, "Minecraft", WindowMode::WINDOWED} {
		FileManager::RegisterDirectory("default", FileManager::GetWorkingDir());
		FileManager::RegisterDirectory("shaders", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\shaders");
		FileManager::RegisterDirectory("textures", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\textures");
		FileManager::RegisterDirectory("models", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\models");
		FileManager::RegisterDirectory("images", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\images");

		Mesh::AddMesh("awp", "models", "AWP_Dragon_Lore.obj");
		ShaderProgram::AddShader("default", "shaders", "default.frag", "default.vert");
		Texture::AddTexture("default", "textures", "awp_color.png", false);
		

		std::shared_ptr<leviathan::Image> im = leviathan::Image::Load("default", "logo.png");
		std::shared_ptr<Window> window = this->GetWindow().lock();
		window->SetWindowIcon(im);


		cam = Camera::GetPrimary();
		wo = new WorldObject();
		wo->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));
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

		 std::shared_ptr<Window> window = this->GetWindow().lock();
		 if (window) {
			 std::stringstream ss;
			 ss << "fps " << fps;
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
			 std::shared_ptr<Camera> camera = cam.lock();
			 if (camera) {
				 MouseMoveEvent* event = (MouseMoveEvent*)ev;
				 double dx, dy;
				 event->GetDelta(&dx, &dy);
				 camera->RotateY((float)-dx);
				 camera->RotateX((float)dy);

				 glm::vec3 cam_angle = camera->GetRotation();
				 //std::cout << cam_angle.x << " | " << cam_angle.y << " | " << cam_angle.z << std::endl;
			 }
		 }
		 
	 }

	 void CheckKeyboardKeys() {
		 std::shared_ptr<Keyboard> keyboard = this->GetKeyboard().lock();
		 if (keyboard) {
			 std::vector<int> pressed_keys;
			 keyboard->GetPressedKeys(&pressed_keys);
			 glm::vec3 move(0.0f);
			 std::shared_ptr<Camera> primary = Camera::GetPrimary();
			 for (int i = 0; i < pressed_keys.size(); i++) {
				 switch (pressed_keys[i]) {
				 case GLFW_KEY_W:
					 move = primary->GetForewardVector();
					 break;
				 case GLFW_KEY_S:
					 move = glm::vec3(-1.0f) * primary->GetForewardVector();
					 break;
				 case GLFW_KEY_A:
					 move = glm::vec3(-1.0f) * primary->GetRightVector();
					 break;
				 case GLFW_KEY_D:
					 move = primary->GetRightVector();
					 break;
				 case GLFW_KEY_SPACE:
					 move = primary->GetUpVector();
					 break;
				 case GLFW_KEY_LEFT_SHIFT:
					 move = glm::vec3(-1.0f) * primary->GetUpVector();
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
				 move = move * glm::vec3(0.25f, 0.25f, 0.25f);
				 primary->Translate(move);
				 glm::vec3 campos = primary->GetPosition();
				 //std::cout << campos.x << " | " << campos.y << " | " << campos.z << std::endl;
			 }
			 
		 }
	 }

	 void OnWindowEvent(Event* event) {
		 if (event->GetType() == EventType::RefreshEvent) {
			 CheckFps();
			 CheckKeyboardKeys();
			 wo->Draw(cam);
		 }
	 }
};
int main() {
	std::shared_ptr<Game> app = std::make_shared<Game>();
	app->Run();
	app.reset();
	return 1;
}