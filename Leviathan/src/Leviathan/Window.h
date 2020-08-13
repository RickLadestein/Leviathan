#pragma once
#include "Core.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Event.h"
#include <functional>
#include <string>
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include <memory>

using EventCallbackFn = std::function<void(Event* e)>;

enum class WindowMode {
	WINDOWED,
	FULLSCREEN,
	WINDOWED_FULLSCREEN
};

struct WindowData {
	friend class Window;

	int width;
	int height;
	int pos_x;
	int pos_y;
	std::string title;
	bool should_close;
	bool focused;

	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<Mouse> mouse;

	WindowMode mode;
	EventCallbackFn WindowCallback;
	EventCallbackFn EventCallback;
};

class LEVIATHAN_API Window {
public:
	Window(int width, int height, std::string title, WindowMode mode);
	~Window();

	bool Open();
	void Close();

	void SetEventCallback(std::function<void(Event* e)>);
	void SetCursorPos(unsigned int x, unsigned int y);
	void SetRawMouseInput(bool val);
	void SetCursorMode(MouseMode mode);
	void ResetGlView();
	void Refresh();


	inline bool GetWindowShouldCloseFlag() { return this->w_data.should_close; };
	inline std::weak_ptr<Keyboard> GetKeyboard() { return this->w_data.keyboard; }
	inline std::weak_ptr<Mouse> GetMouse() { return this->w_data.mouse; }
private:
	void SetWindowCallbacks();
	void OnEvent(Event* event);
	WindowData w_data;
	GLFWwindow* w_handle;
	double last_refresh_time;
};

