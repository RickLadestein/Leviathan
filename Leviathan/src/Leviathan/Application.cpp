#include "Application.h"
#include <iostream>
#include <thread>
Application::Application()
{
	this->window = std::make_shared<Window>(1920, 1080, "Test", WindowMode::WINDOWED);
	this->window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
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
