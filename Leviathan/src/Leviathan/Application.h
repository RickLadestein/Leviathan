#pragma once
#include "Core.h"
#include "Window.h"
#include "Event.h"
#include <memory>

class LEVIATHAN_API Application {
protected:
	Application();
	~Application() = default;
public:
	void Run();
	void Stop();

	virtual void OnEvent(Event* event) {};
	inline std::weak_ptr<Window> GetWindow() { return this->window; }
private:
	std::shared_ptr<Window> window;
};