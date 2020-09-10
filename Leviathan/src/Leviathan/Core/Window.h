#pragma once
#include "Event.h"
#include <functional>
#include <string>
#include "Leviathan/Input/Keyboard.h"
#include "Leviathan/Input/Mouse.h"
#include "Leviathan/Data/Image.h"
#include "Leviathan/Util/Delegate/MultiDelegate.h"
#include <memory>
#include <string>


#include "glad/glad.h"
#include "GLFW/glfw3.h"

typedef void EventCallbackFn(Event* ev);

using util::MultiDelegate;
using util::Delegate;

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
	bool v_sync;

	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<Mouse> mouse;

	WindowMode mode;
	MultiDelegate<EventCallbackFn> EventHandler;
};

class Window {
public:
	Window(int width, int height, std::string title, WindowMode mode);
	~Window();

	bool Open();
	void Close();

	void SetEventCallback(Delegate<EventCallbackFn>& func);
	void SetCursorPos(unsigned int x, unsigned int y);
	void SetRawMouseInput(bool val);
	void SetCursorMode(MouseMode mode);
	void SetSize(int width, int height);
	void SetTitle(std::string title);
	inline void SetClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
	void ResetGlView();
	void Refresh();

	void SetWindowIcon(std::shared_ptr<leviathan::Image> im);
	void SetWindowIcon(unsigned char* data, int width, int height, int components);
	void SetVSync(bool enable);
	void Clear(bool all_buffers);

	inline bool GetWindowShouldCloseFlag() { return this->w_data.should_close; };
	inline std::weak_ptr<Keyboard> GetKeyboard() { return this->w_data.keyboard; }
	inline std::weak_ptr<Mouse> GetMouse() { return this->w_data.mouse; }
	inline MouseMode GetCursorMode() { return this->w_data.mouse->mousemode; }
private:
	void SetWindowCallbacks();
	void OnEvent(Event* event);
	WindowData w_data;
	GLFWimage image;
	GLFWwindow* w_handle;
	double last_refresh_time;
};

