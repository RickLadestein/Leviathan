#pragma once
#include "Core.h"
#include <functional>

enum class EventType{
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
	MouseEvent,
	KeyboardEvent,
	WindowEvent
};

class LEVIATHAN_API  Event {
public:
	inline const EventType GetType() { return this->type; }
	inline const EventCategory GetCategory() { return this->category; }
	virtual inline const char* GetString() { return "Empty event"; }
protected:
	EventCategory category;
	EventType type;
	bool handled;
};

#pragma region Window_Events
class LEVIATHAN_API  RefreshEvent : public Event {
public:
	RefreshEvent(double frametime);
	~RefreshEvent() = default;
	inline double getFrametime() { return frametime; }
	inline const char* GetString() { return  "Window RefreshEvent"; }
private:
	double frametime;
};

class LEVIATHAN_API  ResizeEvent : public Event {
public:
	ResizeEvent(int size_x, int size_y);
	~ResizeEvent() = default;
	inline int getSizeX() { return size_x; }
	inline int getSizeY() { return size_y; }
	inline const char* GetString() { return  "Window ResizeEvent"; }
private:
	int size_x, size_y;
};

class LEVIATHAN_API  MoveEvent : public Event {
public:
	MoveEvent(int x, int y);
	~MoveEvent() = default;
	inline int getPosX() { return x; };
	inline int getPosY() { return y; };
	inline const char* GetString() { return  "Window MoveEvent"; }
private:
	int x, y;
};

class LEVIATHAN_API  FocusEvent : public Event {
public:
	FocusEvent(int hasfocus);
	~FocusEvent() = default;
	inline bool hasFocus() { return hasfocus; };
	inline const char* GetString() { return  "Window FocusEvent"; }
private:
	bool hasfocus;
};
#pragma endregion

#pragma region Mouse_Events
class LEVIATHAN_API  MouseMoveEvent : public Event {
public:
	MouseMoveEvent(double x_pos, double y_pos, double x_delta, double y_delta);
	~MouseMoveEvent() = default;
	inline const char* GetString() { return  "MouseMoveEvent"; }
private:
	double x_pos, y_pos;
	double x_delta, y_delta;
	friend class Mouse;
};

class LEVIATHAN_API  MousePressEvent : public Event {
public:
	MousePressEvent(int button);
	~MousePressEvent() = default;
	inline const char* GetString() { return  "MousePressEvent"; }
private:
	int button;
	friend class Mouse;
};

class LEVIATHAN_API  MouseReleaseEvent : public Event {
public:
	MouseReleaseEvent(int button);
	~MouseReleaseEvent() = default;
	inline const char* GetString() { return  "MouseReleaseEvent"; }
private:
	int button;
	friend class Mouse;
};

class LEVIATHAN_API  MouseWheelEvent : public Event {
public:
	MouseWheelEvent(int scroll);
	~MouseWheelEvent() = default;
	inline const char* GetString() { return  "MouseWheelEvent"; }
private:
	int scroll;
	friend class Mouse;
};
#pragma endregion

#pragma region Keyboard_Event
class LEVIATHAN_API  KeyPressEvent : public Event {
public:
	KeyPressEvent(int key);
	~KeyPressEvent() = default;
	inline const char* GetString() { return  "KeyPressEvent"; }
private:
	int key;
friend class Keyboard;
};

class LEVIATHAN_API  KeyReleaseEvent : public Event {
	friend class Keyboard;
public:
	KeyReleaseEvent(int key);
	~KeyReleaseEvent() = default;
	inline const char* GetString() { return  "KeyReleaseEvent"; }
protected:
	int key;
};

class LEVIATHAN_API  KeyRepeatEvent : public Event {
	friend class Keyboard;
public:
	KeyRepeatEvent(int key);
	~KeyRepeatEvent() = default;
	inline const char* GetString() { return  "KeyRepeatEvent"; }
protected:
	int key;
};

class LEVIATHAN_API  KeyTypeEvent : public Event {
	
public:
	KeyTypeEvent(int key);
	~KeyTypeEvent() = default;
	inline const char* GetString() { return  "KeyTypeEvent"; }
protected:
	int key;
};
#pragma endregion



