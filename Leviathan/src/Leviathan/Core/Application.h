#pragma once
#include "Leviathan/Core.h"
#include "Window.h"
#include "Event.h"
#include <memory>

typedef LEVIATHAN_API std::shared_ptr<Window> WINDOW_PTR;

template class LEVIATHAN_API std::shared_ptr<Window>;
template class LEVIATHAN_API std::weak_ptr<Window>;

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
	WINDOW_PTR window;
};
