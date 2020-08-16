#pragma once
#include "Core.h"
#include <functional>
#include <string>

enum class EventType{
	None,
	MouseMoveEvent,
	MousePressEvent,
	MouseReleaseEvent,
	MouseWheelEvent,

	KeyPressEvent,
	KeyReleaseEvent,
	KeyRepeatEvent,
	KeyTypeEvent,

	RefreshEvent,
	ResizeEvent,
	MoveEvent,
	CloseEvent,
	FocusEvent,
	LostFocusEvent
};

enum class EventCategory {
	None,
	MouseEvent,
	KeyboardEvent,
	WindowEvent
};

class LEVIATHAN_API  Event {
public:
	inline const EventType GetType() { return this->type; }
	inline const EventCategory GetCategory() { return this->category; }
	virtual inline std::string GetString() { return "Empty event"; }
protected:
	EventCategory category = EventCategory::None;
	EventType type = EventType::None;
	bool handled = false;
};

#pragma region Window_Events
class LEVIATHAN_API  RefreshEvent : public Event {
public:
	RefreshEvent(double frametime);
	~RefreshEvent() = default;
	inline double GetFrametime() { return frametime; }
	std::string GetString();
private:
	double frametime;
};

class LEVIATHAN_API  ResizeEvent : public Event {
public:
	ResizeEvent(int size_x, int size_y);
	~ResizeEvent() = default;
	inline void GetSize(int* x, int* y) { *x = size_x; *y = size_y; }
	std::string GetString();
private:
	int size_x, size_y;
};

class LEVIATHAN_API  MoveEvent : public Event {
public:
	MoveEvent(int x, int y);
	~MoveEvent() = default;
	inline void GetPos(int* x, int* y) { *x = this->x; *y = this->y; }
	std::string GetString();
private:
	int x, y;
};

class LEVIATHAN_API  FocusEvent : public Event {
public:
	FocusEvent(int hasfocus);
	~FocusEvent() = default;
	inline bool hasFocus() { return hasfocus; };
	std::string GetString();
private:
	bool hasfocus;
};
#pragma endregion

#pragma region Mouse_Events
class LEVIATHAN_API  MouseMoveEvent : public Event {
public:
	MouseMoveEvent(double x_pos, double y_pos, double x_delta, double y_delta);
	~MouseMoveEvent() = default;
	std::string GetString();
	inline void GetPosition(double* x, double* y) { *x = x_pos; *y = y_pos; }
	inline void GetDelta(double* dx, double* dy) { *dx = x_delta; *dy = y_delta; }
private:
	double x_pos, y_pos;
	double x_delta, y_delta;
	friend class Mouse;
};

class LEVIATHAN_API  MousePressEvent : public Event {
public:
	MousePressEvent(int button);
	~MousePressEvent() = default;
	std::string GetString();
	inline int GetButton() { return button; }
private:
	int button;
	friend class Mouse;
};

class LEVIATHAN_API  MouseReleaseEvent : public Event {
public:
	MouseReleaseEvent(int button);
	~MouseReleaseEvent() = default;
	std::string GetString();
	inline int GetButton() { return button; }
private:
	int button;
	friend class Mouse;
};

class LEVIATHAN_API  MouseWheelEvent : public Event {
public:
	MouseWheelEvent(double x, double y);
	~MouseWheelEvent() = default;
	std::string GetString();
	inline void GetScroll(double* x, double* y) { *x = x_scroll; *y = y_scroll; }
private:
	double x_scroll, y_scroll;
	friend class Mouse;
};
#pragma endregion

#pragma region Keyboard_Event
class LEVIATHAN_API  KeyPressEvent : public Event {
public:
	KeyPressEvent(int key);
	~KeyPressEvent() = default;
	std::string GetString();
	inline int GetKey() { return key; }
private:
	int key;
friend class Keyboard;
};

class LEVIATHAN_API  KeyReleaseEvent : public Event {
	friend class Keyboard;
public:
	KeyReleaseEvent(int key);
	~KeyReleaseEvent() = default;
	std::string GetString();
	inline int GetKey() { return key; }
protected:
	int key;
};

class LEVIATHAN_API  KeyRepeatEvent : public Event {
	friend class Keyboard;
public:
	KeyRepeatEvent(int key);
	~KeyRepeatEvent() = default;
	std::string GetString();
	inline int GetKey() { return key; }
protected:
	int key;
};

class LEVIATHAN_API  KeyTypeEvent : public Event {
	
public:
	KeyTypeEvent(int key);
	~KeyTypeEvent() = default;
	std::string GetString();
	inline int GetKey() { return key; }
protected:
	int key;
};
#pragma endregion



