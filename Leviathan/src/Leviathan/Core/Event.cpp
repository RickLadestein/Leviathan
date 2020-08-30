#include "Event.h"
#include <sstream>

RefreshEvent::RefreshEvent(double frametime)
{
	this->type = EventType::RefreshEvent;
	this->category = EventCategory::WindowEvent;
	this->frametime = frametime;
	this->handled = false;
}

std::string RefreshEvent::GetString()
{
	std::stringstream ss;
	ss << "RefreshEvent[Frametime: " << this->frametime << "]";
	return ss.str();
}

ResizeEvent::ResizeEvent(int size_x, int size_y)
{
	this->type = EventType::ResizeEvent;
	this->category = EventCategory::WindowEvent;
	this->size_x = size_x;
	this->size_y = size_y;
	this->handled = false;
}

std::string ResizeEvent::GetString()
{
	std::stringstream ss;
	ss << "ResizeEvent[Resize to: " << this->size_x << ", " << this->size_y << "]";
	return ss.str();
}

MoveEvent::MoveEvent(int x, int y)
{
	this->type = EventType::MoveEvent;
	this->category = EventCategory::WindowEvent;
	this->x = x;
	this->y = y;
	this->handled = false;
}

std::string MoveEvent::GetString()
{
	std::stringstream ss;
	ss << "MoveEvent[Moved to: " << this->x << ", " << this->y << "]";
	return ss.str();
}

FocusEvent::FocusEvent(int hasfocus)
{
	this->type = EventType::FocusEvent;
	this->category = EventCategory::WindowEvent;
	this->handled = false;
	this->hasfocus = hasfocus;
}

std::string FocusEvent::GetString()
{
	std::stringstream ss;
	ss << "MoveEvent[Focus: " << this->hasfocus << "]";
	return ss.str();
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

std::string MouseMoveEvent::GetString()
{
	std::stringstream ss;
	ss << "MouseMoveEvent[ Pos:" << this->x_pos << "," << this->y_pos <<
		" Delta" << this->x_delta << "," << this->y_delta << "]";
	return ss.str();
}

MousePressEvent::MousePressEvent( int button)
{
	this->type = EventType::MousePressEvent;
	this->category = EventCategory::MouseEvent;
	this->button = button;
	this->handled = false;
}

std::string MousePressEvent::GetString()
{
	std::stringstream ss;
	ss << "MousePressEvent[ Btn:" << this->button << "]";
	return ss.str();
}

MouseReleaseEvent::MouseReleaseEvent(int button)
{
	this->type = EventType::MouseReleaseEvent;
	this->category = EventCategory::MouseEvent;
	this->button = button;
	this->handled = false;
}

std::string MouseReleaseEvent::GetString()
{
	std::stringstream ss;
	ss << "MouseReleaseEvent[ Btn:" << this->button << "]";
	return ss.str();
}

MouseWheelEvent::MouseWheelEvent(double x, double y)
{
	this->type = EventType::MouseWheelEvent;
	this->category = EventCategory::MouseEvent;
	this->x_scroll = x;
	this->y_scroll = y;
	this->handled = false;
}

std::string MouseWheelEvent::GetString()
{
	std::stringstream ss;
	ss << "MouseWheelEvent[ Scroll:" << this->x_scroll << ", " << this->y_scroll << "]";
	return ss.str();
}

KeyPressEvent::KeyPressEvent(int key)
{
	this->type = EventType::KeyPressEvent;
	this->category = EventCategory::KeyboardEvent;
	this->key = key;
	this->handled = false;
}

std::string KeyPressEvent::GetString()
{
	std::stringstream ss;
	ss << "KeyPressEvent[ Key:" << this->key << "]";
	return ss.str();
}

KeyReleaseEvent::KeyReleaseEvent(int key)
{
	this->type = EventType::KeyReleaseEvent;
	this->category = EventCategory::KeyboardEvent;
	this->key = key;
	this->handled = false;
}

std::string KeyReleaseEvent::GetString()
{
	std::stringstream ss;
	ss << "KeyReleaseEvent[ Key:" << this->key << "]";
	return ss.str();
}

KeyTypeEvent::KeyTypeEvent(int key)
{
	this->type = EventType::KeyTypeEvent;
	this->category = EventCategory::KeyboardEvent;
	this->key = key;
	this->handled = false;
}

std::string KeyTypeEvent::GetString()
{
	std::stringstream ss;
	ss << "KeyTypeEvent[ Key:" << this->key << "]";
	return ss.str();
}

KeyRepeatEvent::KeyRepeatEvent(int key)
{
	this->key = key;
}

std::string KeyRepeatEvent::GetString()
{
	std::stringstream ss;
	ss << "KeyRepeatEvent[ Key:" << this->key << "]";
	return ss.str();
}
