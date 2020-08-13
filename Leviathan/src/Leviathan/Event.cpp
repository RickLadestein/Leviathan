#include "Event.h"

RefreshEvent::RefreshEvent(double frametime)
{
	this->type = EventType::RefreshEvent;
	this->category = EventCategory::WindowEvent;
	this->frametime = frametime;
	this->handled = false;
}

ResizeEvent::ResizeEvent(int size_x, int size_y)
{
	this->type = EventType::ResizeEvent;
	this->category = EventCategory::WindowEvent;
	this->size_x = size_x;
	this->size_y = size_y;
	this->handled = false;
}

MoveEvent::MoveEvent(int x, int y)
{
	this->type = EventType::MoveEvent;
	this->category = EventCategory::WindowEvent;
	this->x = x;
	this->y = y;
	this->handled = false;
}

FocusEvent::FocusEvent(int hasfocus)
{
	this->type = EventType::FocusEvent;
	this->category = EventCategory::WindowEvent;
	this->handled = false;
	this->hasfocus = hasfocus;
}

MouseMoveEvent::MouseMoveEvent(double x_pos, double y_pos, double x_delta, double y_delta)
{
	this->type = EventType::MouseMoveEvent;
	this->category = EventCategory::MouseEvent;
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->x_delta = x_delta;
	this->y_delta = y_delta;
	this->handled = false;
}

MousePressEvent::MousePressEvent( int button)
{
	this->type = EventType::MousePressEvent;
	this->category = EventCategory::MouseEvent;
	this->button = button;
	this->handled = false;
}

MouseReleaseEvent::MouseReleaseEvent(int button)
{
	this->type = EventType::MouseReleaseEvent;
	this->category = EventCategory::MouseEvent;
	this->button = button;
	this->handled = false;
}

MouseWheelEvent::MouseWheelEvent(int scroll)
{
	this->type = EventType::MouseWheelEvent;
	this->category = EventCategory::MouseEvent;
	this->scroll = scroll;
	this->handled = false;
}

KeyPressEvent::KeyPressEvent(int key)
{
	this->type = EventType::KeyPressEvent;
	this->category = EventCategory::KeyboardEvent;
	this->key = key;
	this->handled = false;
}

KeyReleaseEvent::KeyReleaseEvent(int key)
{
	this->type = EventType::KeyReleaseEvent;
	this->category = EventCategory::KeyboardEvent;
	this->key = key;
	this->handled = false;
}

KeyTypeEvent::KeyTypeEvent(int key)
{
	this->type = EventType::KeyTypeEvent;
	this->category = EventCategory::KeyboardEvent;
	this->key = key;
	this->handled = false;
}

KeyRepeatEvent::KeyRepeatEvent(int key)
{
	this->key = key;
}
