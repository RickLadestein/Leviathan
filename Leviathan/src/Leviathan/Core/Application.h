#pragma once
#include "Leviathan/Data/Object.h"
#include "Window.h"
#include "Event.h"

#include <string>
#include <sstream>
#include <memory>
#include <iostream>

typedef std::shared_ptr<Leviathan::Window> WINDOW_PTR;

namespace Leviathan {
	class Application : public Object {
	protected:
		Application();
		Application(int width, int height, std::string title, WindowMode mode);
		~Application() { if (this->open) { this->Stop(); } this->open = false; }
	public:
		void Run();
		void Stop();

		std::weak_ptr<Leviathan::Input::Keyboard> GetKeyboard();
		std::weak_ptr<Leviathan::Input::Mouse> GetMouse();

		virtual void OnEvent(Leviathan::Events::Event* event) {};
		inline std::weak_ptr<Window> GetWindow() { return this->window; }

		std::string ToString() override;
	private:
		WINDOW_PTR window;
		bool open;
	};
}
