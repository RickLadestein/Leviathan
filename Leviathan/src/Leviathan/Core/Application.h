#pragma once
#include "Leviathan/Core.h"
#include "Window.h"
#include "Event.h"
#include <memory>

typedef std::shared_ptr<Window> WINDOW_PTR;

class Application {
protected:
	Application();
	~Application() = default;
public:
	void Run();
	void Stop();

	virtual void OnEvent(Event* event) {};
	inline std::weak_ptr<Window> GetWindow() { return this->window; }
private:
	WINDOW_PTR window;
};
