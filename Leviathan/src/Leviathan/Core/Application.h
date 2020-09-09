#pragma once
#include "Leviathan/Core.h"
#include "Window.h"
#include "Event.h"
#include <string>
#include <memory>

typedef std::shared_ptr<Window> WINDOW_PTR;

class Application {
protected:
	Application();
	Application(int width, int height, std::string title, WindowMode mode);
	~Application() = default;
public:
	void Run();
	void Stop();

	std::weak_ptr<Keyboard> GetKeyboard();
	std::weak_ptr<Mouse> GetMouse();

	virtual void OnEvent(Event* event) {};
	inline std::weak_ptr<Window> GetWindow() { return this->window; }
private:
	WINDOW_PTR window;
};
