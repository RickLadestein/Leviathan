#include "Application.h"
#include "Leviathan/Graphics/Camera.h"
#include <iostream>
#include <thread>
Application::Application()
{
	Camera::GetPrimary();
	this->window = std::make_shared<Window>(500, 500, "Test", WindowMode::WINDOWED);
	this->window->SetEventCallback(util::Delegate<EventCallbackFn>(this, &Application::OnEvent));
	this->window->SetRawMouseInput(true);
	this->window->Open();
}

Application::Application(int width, int height, std::string title, WindowMode mode)
{
	Camera::GetPrimary();
	this->window = std::make_shared<Window>(width, height, title, mode);
	this->window->SetEventCallback(util::Delegate<EventCallbackFn>(this, &Application::OnEvent));
	this->window->Open();
}

void Application::Run()
{
	while (!this->window->GetWindowShouldCloseFlag()) {
		this->window->Refresh();
	}
	return;
}

void Application::Stop()
{
	this->window->Close();
}

std::weak_ptr<Keyboard> Application::GetKeyboard()
{
	if (this->window) {
		return this->window->GetKeyboard();
	}
	return std::weak_ptr<Keyboard>();
}

std::weak_ptr<Mouse> Application::GetMouse()
{
	if (this->window) {
		return this->window->GetMouse();
	}
	return std::weak_ptr<Mouse>();
}
