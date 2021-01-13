#include "Window.h"
#include "Leviathan/Graphics/Buffers/DepthBuffer.h"
#include "Leviathan/Graphics/Buffers/StencilBuffer.h"

#include <iostream>
#include <sstream>
void GLAPIENTRY OnGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void APIENTRY OnGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::stringstream ss;
	ss << "GL debug message received \n"
		<< "source: " << source << "\n"
		<< "type: " << type << "\n"
		<< "severity: " << severity << "\n"
		<< message;
	std::cout << ss.str() << std::endl;
	if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM)
		__debugbreak();
}


using Leviathan::Graphics::Buffers::DepthBuffer;
using Leviathan::Graphics::Buffers::StencilBuffer;
namespace Leviathan {
	/**
	 * @brief Creates a new instance of window
	 * @param width Window width
	 * @param height Window height
	 * @param title Window Title
	 * @param mode Window mode (Fullscreen, Windowed, Windowed_Fullscreen)
	*/
	Window::Window(int width, int height, std::string title, WindowMode mode)
	{
		this->w_data.width = width;
		this->w_data.height = height;
		this->w_data.should_close = false;
		this->last_refresh_time = 0;
		this->w_data.pos_x = 0;
		this->w_data.pos_y = 0;
		this->w_data.mode = mode;
		this->w_data.focused = true;
		this->w_data.title = title;
		this->w_data.keyboard = std::make_shared<Leviathan::Input::Keyboard>();
		this->w_data.mouse = std::make_shared<Leviathan::Input::Mouse>();
		this->w_data.v_sync = true;
		this->image.pixels = nullptr;
	}


	/**
	 * @brief Opens the window with specified parameters at startup
	 * @return Window open succes
	*/
	bool Window::Open()
	{
		if (glfwInit() != GLFW_TRUE) {
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

		if (!monitor && !vidmode) {
			// Error occured
			return false;
		}

		switch (this->w_data.mode) {
		case WindowMode::WINDOWED:
			this->w_handle = glfwCreateWindow(this->w_data.width, this->w_data.height, this->w_data.title.c_str(), NULL, NULL);
			break;
		case WindowMode::FULLSCREEN:
			this->w_handle = glfwCreateWindow(vidmode->width, vidmode->height, this->w_data.title.c_str(), monitor, NULL);
			this->w_data.width = vidmode->width;
			this->w_data.height = vidmode->height;
			break;
		case WindowMode::WINDOWED_FULLSCREEN:
			glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

			this->w_handle = glfwCreateWindow(vidmode->width, vidmode->height, this->w_data.title.c_str(), monitor, NULL);
			this->w_data.width = vidmode->width;
			this->w_data.height = vidmode->height;
			break;
		}
		if (!w_handle) {
			return false;
		}
		glfwMakeContextCurrent(this->w_handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status) {
			std::cout << "Failed to initialize glad" << std::endl;
		}

		//Set the window position data
		int pos_x, pos_y;
		glfwGetWindowPos(this->w_handle, &pos_x, &pos_y);
		this->w_data.pos_x = pos_x;
		this->w_data.pos_y = pos_y;

		//Set the window aspect ratio
		this->SetWindowCallbacks();
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		this->ResetGlView();

		glfwSetWindowUserPointer(this->w_handle, &this->w_data);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OnGlError, 0);
		return true;
	}

	/**
	 * @brief Indicates to the window that the window should close.
			  All resources that the window manages are released and Window safe to be freed from memory afterwards
	*/
	void Window::Close()
	{
		this->w_data.should_close = true;
		if (this->w_handle) {
			glfwSetWindowShouldClose(this->w_handle, GLFW_TRUE);
			glfwDestroyWindow(this->w_handle);
			this->w_handle = nullptr;
		}
		if (this->image.pixels) {
			delete[] this->image.pixels;
			this->image.pixels = nullptr;
		}
		//Delete unmanaged resources
	}

	/**
	 * @brief Resets the OpenGL draw window to the window's own width and height
	*/
	void Window::ResetGlView()
	{
		glViewport(0, 0, this->w_data.width, this->w_data.height);
	}

	void Window::Refresh()
	{
		this->Clear(true);
		double current_time = glfwGetTime();
		float frame_delta = float(current_time - this->last_refresh_time);
		Leviathan::Events::RefreshEvent ev(frame_delta);
		w_data.EventHandler.Broadcast(&ev);
		this->last_refresh_time = current_time;

		if (this->w_data.v_sync) {
			glfwSwapBuffers(this->w_handle);
		}
		else {
			glFlush();
		}

		glfwPollEvents();
	}

	/**
	 * @brief Sets the window icon to Leviathan API imported image
	 * @param im Imported image to be used as icon
	*/
	void Window::SetWindowIcon(std::shared_ptr<Leviathan::Image> im)
	{
		if (im == nullptr) {
			return;
		}
		//get rid of the old image
		if (this->image.pixels) {
			delete[] this->image.pixels;
		}
		int components = im->GetChannelCount();
		if (components < 4 || components > 4) {
			std::cerr << "Could not use image: image needs to have RGBA components" << std::endl;
		}
		int width, height, char_cnt;
		im->GetDimensions(&width, &height);
		char_cnt = (width * height) * components;
		this->image.pixels = new unsigned char[char_cnt];
		memcpy(this->image.pixels, im->GetDataPtr(), (char_cnt * sizeof(unsigned char)));
		this->image.width = width;
		this->image.height = height;
		glfwSetWindowIcon(this->w_handle, 1, &this->image);
	}

	/**
	 * @brief Sets the window icon to custom imported window icon specifications
	 * @param data Pixel data of the icon
	 * @param width Icon width
	 * @param height Icon height
	 * @param components Icon color components (RGB, RGBA)
	*/
	void Window::SetWindowIcon(unsigned char* data, int width, int height, int components)
	{
		if (this->image.pixels) {
			delete[] this->image.pixels;
		}
		if (components < 4 || components > 4) {
			std::cerr << "Could not use image: image needs to have RGBA components" << std::endl;
		}
		int char_cnt = (width * height) * components;
		this->image.pixels = new unsigned char[char_cnt];
		memcpy(this->image.pixels, data, (char_cnt * sizeof(unsigned char)));
		this->image.width = width;
		this->image.height = height;
		glfwSetWindowIcon(this->w_handle, 1, &this->image);
	}

	/**
	 * @brief Changes the application render strategy to enable or disable Vsync
	 * @param enable Enable or Disable Vsync
	*/
	void Window::SetVSync(bool enable)
	{
		this->w_data.v_sync = enable;
		if (enable)
			glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
		else
			glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	}

	/**
	 * @brief Clears the screen buffer or all enabled buffers if specified in argument
	 * @param all_buffers Clear all buffers argument
	*/
	void Window::Clear(bool all_buffers)
	{
		if (all_buffers) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			return;
		}
		else {
			glClear(GL_COLOR_BUFFER_BIT);
			if (DepthBuffer::IsEnabled()) {
				glClear(GL_DEPTH_BUFFER_BIT);
			}
			if (StencilBuffer::IsEnabled()) {
				glClear(GL_STENCIL_BUFFER_BIT);
			}
			return;
		}

	}

	/**
	 * @brief Sets the Event listener function to be called whenever an event is generated in the window
	 * @param event Event delegate to be executed
	*/

	void Window::SetEventCallback(Delegate<EventCallbackFn>& func)
	{
		this->w_data.EventHandler += func;
	}

	/**
	 * @brief Sets the cursorposition in the window
	 * @param x X-coordinate inside window
	 * @param y Y-coordinate inside window
	*/
	void Window::SetCursorPos(unsigned int x, unsigned int y)
	{
		int pos_x = x, pos_y = y;
		if (pos_x >= this->w_data.width) {
			pos_x = this->w_data.width - 1;
		}

		if (pos_y >= this->w_data.height) {
			pos_y = this->w_data.height - 1;
		}
		glfwSetCursorPos(this->w_handle, pos_x, pos_y);
	}

	/**
	 * @brief Bypass the windows mouse input to raw input from mouse
	 * @param val Enables or Disables raw mouse input
	*/
	void Window::SetRawMouseInput(bool val)
	{
		if (glfwRawMouseMotionSupported()) {
			if (val) {
				glfwSetInputMode(this->w_handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
				this->w_data.mouse->SetMouseInputMode(Leviathan::Input::MouseInputMode::RAW);
			}
			else {
				glfwSetInputMode(this->w_handle, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
				this->w_data.mouse->SetMouseInputMode(Leviathan::Input::MouseInputMode::DEFAULT);
			}
		}
	}

	/**
	 * @brief Sets the cursor visibility and behaviour
	 * @param mode Behaviour that the cursor should have
	*/
	void Window::SetCursorMode(Leviathan::Input::MouseMode mode)
	{
		double time = glfwGetTime();
		if (time - this->w_data.mouse->GetLastMouseUpdate() < 0.25) {
			return;
		}
		this->w_data.mouse->SetLastMouseUpdate(time);

		switch (mode) {
		case Leviathan::Input::MouseMode::VISIBLE:
			glfwSetInputMode(this->w_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case Leviathan::Input::MouseMode::INVISIBLE:
			glfwSetInputMode(this->w_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		case Leviathan::Input::MouseMode::CENTERED:
			glfwSetInputMode(this->w_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		}
		this->w_data.mouse->SetMouseMode(mode);
	}

	/**
	 * @brief Sets the window size
	 * @param width Width of window
	 * @param height Height of window
	*/
	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(this->w_handle, width, height);
	}

	/**
	 * @brief Sets the window title
	 * @param title Title of window
	*/
	void Window::SetTitle(std::string title)
	{
		glfwSetWindowTitle(this->w_handle, title.c_str());
	}

	void Window::SetWindowCallbacks()
	{
		glfwSetWindowSizeCallback(w_handle, [](GLFWwindow* w_handle, int width, int height)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				w_data->width = width;
				w_data->height = height;
				Leviathan::Events::ResizeEvent ev(width, height);
				w_data->EventHandler.Broadcast(&ev);
			});

		glfwSetWindowPosCallback(w_handle, [](GLFWwindow* w_handle, int x, int y)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				w_data->pos_x = x;
				w_data->pos_y = y;
				Leviathan::Events::MoveEvent ev(x, y);
				w_data->EventHandler.Broadcast(&ev);
			});
		glfwSetWindowFocusCallback(w_handle, [](GLFWwindow* w_handle, int focused)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				Leviathan::Events::FocusEvent ev(focused);
				w_data->EventHandler.Broadcast(&ev);
			});
		glfwSetWindowCloseCallback(w_handle, [](GLFWwindow* w_handle)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				w_data->should_close = true;
			});
		glfwSetKeyCallback(w_handle, [](GLFWwindow* w_handle, int key, int scancode, int action, int mods)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				switch (action) {
				case GLFW_PRESS:
				{
					Leviathan::Events::KeyPressEvent ev(key);
					w_data->keyboard->onKeyEvent(&ev);
					w_data->EventHandler.Broadcast(&ev);
					break;
				}
				case GLFW_RELEASE:
				{
					Leviathan::Events::KeyReleaseEvent ev(key);
					w_data->keyboard->onKeyEvent(&ev);
					w_data->EventHandler.Broadcast(&ev);
					break;
				}
				case GLFW_REPEAT:
				{
					Leviathan::Events::KeyRepeatEvent ev(key);
					w_data->EventHandler.Broadcast(&ev);
				}
				break;
				}
			});
		glfwSetCharCallback(w_handle, [](GLFWwindow* w_handle, unsigned int unicode_key)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				Leviathan::Events::KeyTypeEvent ev(unicode_key);
				if (w_data->keyboard->GetKeyboardMode() == Leviathan::Input::KeyboardMode::TYPING) {
					w_data->EventHandler.Broadcast(&ev);
				}
			});

		glfwSetMouseButtonCallback(w_handle, [](GLFWwindow* w_handle, int btn, int action, int mods)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				switch (action) {
				case GLFW_PRESS:
				{
					Leviathan::Events::MousePressEvent ev(btn);
					w_data->mouse->onEvent(&ev);
					w_data->EventHandler.Broadcast(&ev);
				}
				break;
				case GLFW_RELEASE:
				{
					Leviathan::Events::MouseReleaseEvent ev(btn);
					w_data->mouse->onEvent(&ev);
					w_data->EventHandler.Broadcast(&ev);
				}
				break;
				}
			});
		glfwSetCursorPosCallback(w_handle, [](GLFWwindow* w_handle, double pos_x, double pos_y)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				double m_x, m_y, d_x, d_y;
				w_data->mouse->GetMousePosition(&m_x, &m_y);
				d_x = m_x - pos_x;
				d_y = m_y - pos_y;
				Leviathan::Events::MouseMoveEvent ev(pos_x, pos_y, d_x, d_y);
				w_data->mouse->onEvent(&ev);
				w_data->EventHandler.Broadcast(&ev);
			});
		glfwSetScrollCallback(w_handle, [](GLFWwindow* w_handle, double x_scroll, double y_scroll)
			{
				WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
				Leviathan::Events::MouseWheelEvent ev(x_scroll, y_scroll);
				w_data->EventHandler.Broadcast(&ev);
			});
	}

	void Window::OnEvent(Leviathan::Events::Event* event)
	{
		switch (event->GetEventType()) {
		case Leviathan::Events::EventType::WindowResize:
		{
			Leviathan::Events::ResizeEvent* ev1 = dynamic_cast<Leviathan::Events::ResizeEvent*> (event);
			ev1->GetSize(&this->w_data.width, &this->w_data.height);
			this->ResetGlView();
		}
		break;
		case Leviathan::Events::EventType::WindowMove:
		{
			Leviathan::Events::MoveEvent* ev2 = dynamic_cast<Leviathan::Events::MoveEvent*> (event);
			ev2->GetPos(&this->w_data.pos_x, &this->w_data.pos_y);
		}
		break;
		case Leviathan::Events::EventType::WindowFocus:
		{
			Leviathan::Events::FocusEvent* ev3 = dynamic_cast<Leviathan::Events::FocusEvent*> (event);
			this->w_data.focused = ev3->hasFocus();
		}
		break;
		}
	}
}
