#include <Leviathan.h>
#include <functional>
#include "Leviathan/Util/FileManager.h"
#include <iostream>
#include <string>
#include "Leviathan/Data/Image.h"
#include "Leviathan/Graphics/Shader.h"
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
	std::shared_ptr<Camera> cam;
	Game() {
		FileManager::RegisterDirectory("default", FileManager::GetWorkingDir());
		FileManager::RegisterDirectory("shaders", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\shaders");
		FileManager::RegisterDirectory("textures", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\textures");
		FileManager::RegisterDirectory("models", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\models");
		FileManager::RegisterDirectory("images", "C:\\Users\\rladestein\\source\\repos\\Leviathan\\Sandbox\\resources\\images");
		GLenum error = glGetError();
		Mesh::AddMesh("awp", "models", "AWP_Dragon_Lore.obj");
		error = glGetError();
		ShaderProgram::AddShader("default", "shaders", "default.frag", "default.vert");
		error = glGetError();
		Texture::AddTexture("default", "textures", "awp_color.png", false);
		error = glGetError();
		

		std::shared_ptr<leviathan::Image> im = leviathan::Image::Load("default", "logo.png");
		std::shared_ptr<Window> window = this->GetWindow().lock();
		window->SetWindowIcon(im);
		window->SetTitle("Minecraft");


		cam = std::make_shared<Camera>();
		wo = new WorldObject();
		wo->setPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	}
	~Game() = default;

	 void OnEvent(Event* event) override {
		if (event->GetCategory() == EventCategory::WindowEvent && event->GetType() == EventType::RefreshEvent) {
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