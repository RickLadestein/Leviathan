#include "Window.h"
#include <iostream>


Window::Window(int width, int height, std::string title, WindowMode mode)
{
	this->w_data.width = width;
	this->w_data.height = height;
	this->w_data.WindowCallback = std::bind(&Window::OnEvent, this, std::placeholders::_1);
	this->w_data.should_close = false;
	this->last_refresh_time = 0;
	this->w_data.pos_x = 0;
	this->w_data.pos_y = 0;
	this->w_data.mode = mode;
	this->w_data.focused = true;
	this->w_data.title = title;
	this->w_data.keyboard = std::make_shared<Keyboard>();
	this->w_data.mouse = std::make_shared<Mouse>();
	this->image.pixels = nullptr;
}

Window::~Window()
{
	if(this->image.pixels)
		delete[] this->image.pixels;
}

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
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->ResetGlView();

	glfwSetWindowUserPointer(this->w_handle, &this->w_data);
	return true;
}

void Window::Close()
{
	this->w_data.should_close = true;
	glfwSetWindowShouldClose(this->w_handle, GLFW_TRUE);
	glfwDestroyWindow(this->w_handle);
	//Delete unmanaged resources
}

void Window::ResetGlView()
{
	glViewport(0, 0, this->w_data.width, this->w_data.height);
}

void Window::Refresh()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double current_time = glfwGetTime();
	RefreshEvent ev(current_time - this->last_refresh_time);
	w_data.EventCallback(&ev);
	this->last_refresh_time = current_time;
	glfwSwapBuffers(this->w_handle);
	glfwPollEvents();
}

void Window::SetWindowIcon(std::shared_ptr<leviathan::Image> im)
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

void Window::SetEventCallback(std::function<void(Event* e)> event)
{
	this->w_data.EventCallback = event;
}

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

void Window::SetRawMouseInput(bool val)
{
	if (glfwRawMouseMotionSupported()) {
		if (val) {
			glfwSetInputMode(this->w_handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			this->w_data.mouse->mouseinputmode = MouseInputMode::RAW;
		}
		else {
			glfwSetInputMode(this->w_handle, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
			this->w_data.mouse->mouseinputmode = MouseInputMode::DEFAULT;
		}
	}
}

void Window::SetCursorMode(MouseMode mode)
{
	double time = glfwGetTime();
	if (time - this->w_data.mouse->last_mode_update < 0.25) {
		return;
	}
	this->w_data.mouse->last_mode_update = time;

	switch (mode) {
	case MouseMode::VISIBLE:
		glfwSetInputMode(this->w_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case MouseMode::INVISIBLE:
		glfwSetInputMode(this->w_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case MouseMode::CENTERED:
		glfwSetInputMode(this->w_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	}
	this->w_data.mouse->mousemode = mode;
}

void Window::SetSize(int width, int height)
{
	glfwSetWindowSize(this->w_handle, width, height);
}

void Window::SetTitle(std::string title)
{
	glfwSetWindowTitle(this->w_handle, title.c_str());
}

void Window::SetWindowCallbacks()
{
	glfwSetWindowSizeCallback(w_handle, [](GLFWwindow* w_handle, int width, int height)
		{
			WindowData* w_data = (WindowData*) glfwGetWindowUserPointer(w_handle);
			w_data->width = width;
			w_data->height = height;
			ResizeEvent ev(width, height);
			w_data->WindowCallback(&ev);
			w_data->EventCallback(&ev);
		});

	glfwSetWindowPosCallback(w_handle, [](GLFWwindow* w_handle, int x, int y)
		{
			WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
			w_data->pos_x = x;
			w_data->pos_y = y;
			MoveEvent ev(x, y);
			w_data->WindowCallback(&ev);
			w_data->EventCallback(&ev);
		});
	glfwSetWindowFocusCallback(w_handle, [](GLFWwindow* w_handle, int focused)
		{
			WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
			FocusEvent ev(focused);
			w_data->WindowCallback(&ev);
			w_data->EventCallback(&ev);
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
					KeyPressEvent ev(key);
					w_data->keyboard->onKeyEvent(&ev);
					w_data->EventCallback(&ev);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent ev(key);
					w_data->keyboard->onKeyEvent(&ev);
					w_data->EventCallback(&ev);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyRepeatEvent ev(key);
					w_data->EventCallback(&ev);
				}
				break;
			}
		});
	glfwSetCharCallback(w_handle, [](GLFWwindow* w_handle, unsigned int unicode_key)
		{
			WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
			KeyTypeEvent ev(unicode_key);
			if (w_data->keyboard->GetKeyboardMode() == KeyboardMode::TYPING) {
				w_data->EventCallback(&ev);
			}
		});

	glfwSetMouseButtonCallback(w_handle, [](GLFWwindow* w_handle, int btn, int action, int mods)
		{
			WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
			switch (action) {
			case GLFW_PRESS:
			{
				MousePressEvent ev(btn);
				w_data->mouse->onEvent(&ev);
				w_data->EventCallback(&ev);
			}
				break;
			case GLFW_RELEASE:
			{
				MouseReleaseEvent ev(btn);
				w_data->mouse->onEvent(&ev);
				w_data->EventCallback(&ev);
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
			MouseMoveEvent ev(pos_x, pos_y, d_x, d_y);
			w_data->mouse->onEvent(&ev);
			w_data->EventCallback(&ev);
		});
	glfwSetScrollCallback(w_handle, [](GLFWwindow* w_handle, double x_scroll, double y_scroll) 
		{
			WindowData* w_data = (WindowData*)glfwGetWindowUserPointer(w_handle);
			MouseWheelEvent ev(x_scroll, y_scroll);
			w_data->EventCallback(&ev);
		});
}

void Window::OnEvent(Event* event)
{
	switch (event->GetType()) {
	case EventType::ResizeEvent:
	{
		ResizeEvent* ev1 = dynamic_cast<ResizeEvent*> (event);
		ev1->GetSize(&this->w_data.width, &this->w_data.height);
		this->ResetGlView();
	}
		break;
	case EventType::MoveEvent:
	{
		MoveEvent* ev2 = dynamic_cast<MoveEvent*> (event);
		ev2->GetPos(&this->w_data.pos_x, &this->w_data.pos_y);
	}
		break;
	case EventType::FocusEvent:
	{
		FocusEvent* ev3 = dynamic_cast<FocusEvent*> (event);
		this->w_data.focused = ev3->hasFocus();
	}
		break;
	}
}
