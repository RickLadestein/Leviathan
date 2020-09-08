#include <Leviathan.h>
#include <functional>
#include "Leviathan/Util/FileManager.h"
#include <iostream>
#include <string>
#include "Leviathan/Data/Image.h"
#include "Leviathan/Graphics/Shader.h"
#include <memory>

class Game : public Application {
public:
	Game() = default;
	~Game() = default;

	 void OnEvent(Event* event) override {
		if (event->GetCategory() == EventCategory::MouseEvent) {
			std::cout << event->GetString() << std::endl;
		}
	 }
};
int main() {
	std::cout << "opening window" << std::endl;
	std::shared_ptr<Game> app = std::make_shared<Game>();

	std::cout << "importing shaders" << std::endl;
	FileManager::RegisterDirectory("default", FileManager::GetWorkingDir());
	FileManager::RegisterDirectory("shaders", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\shaders");
	FileManager::RegisterDirectory("textures", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\textures");
	FileManager::RegisterDirectory("models", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\models");
	FileManager::RegisterDirectory("images", "C:\\Users\\dazle\\source\\repos\\Leviathan\\Sandbox\\resources\\images");

	std::cout << "loading logo" << std::endl;
	std::shared_ptr<leviathan::Image> im = leviathan::Image::Load("default", "logo.png");
	ShaderProgram::AddShader("default", "shaders", "default.frag", "default.vert");
	ShaderProgram::DeleteShader("default");
	std::shared_ptr<Window> window = app->GetWindow().lock();
	window->SetWindowIcon(im);
	window->SetTitle("Minecraft");

	std::cout << "starting application" << std::endl;
	app->Run();
	app.reset();
	return 1;
}