#include "Mouse.h"

Mouse::Mouse()
{
	this->pos_x = 0;
	this->pos_y = 0;
	this->x_delta = 0;
	this->y_delta = 0;
	mouse_btns = new int[MAX_MOUSE_PRESS];
	for (int i = 0; i < MAX_MOUSE_PRESS; i++) {
		mouse_btns[i] = -1;
	}
	this->mouseinputmode = MouseInputMode::DEFAULT;
	this->mousemode = MouseMode::VISIBLE;
}

Mouse::~Mouse()
{
	delete[] mouse_btns;
}

void Mouse::GetMousePosition(double* x, double* y)
{
	*x = this->pos_x;
	*y = this->pos_y;
}

void Mouse::onEvent(Event* event)
{
	switch (event->GetType()) {
	case EventType::MouseMoveEvent:
	{
		MouseMoveEvent* ev = dynamic_cast<MouseMoveEvent*> (event);
		this->pos_x = ev->x_pos;
		this->pos_y = ev->y_pos;
		this->x_delta = ev->x_delta;
		this->y_delta = ev->y_delta;
	}
	break;
	case EventType::MousePressEvent:
	{
		MousePressEvent* ev = dynamic_cast<MousePressEvent*> (event);
		this->AddBtn(ev->button);
	}
	break;
	case EventType::MouseReleaseEvent:
	{
		MouseReleaseEvent* ev = dynamic_cast<MouseReleaseEvent*> (event);
		this->RemoveBtn(ev->button);
	}
	break;
	}
}

bool Mouse::CheckIfBtnIsPressed(int btn)
{
	for (int i = 0; i < MAX_MOUSE_PRESS; i++) {
		if (mouse_btns[i] == btn) {
			return true;
		}
	}
	return false;
}

void Mouse::AddBtn(int btn)
{
	if (!CheckIfBtnIsPressed(btn)) {
		for (int i = 0; i < MAX_MOUSE_PRESS; i++) {
			if (mouse_btns[i] == -1) {
				mouse_btns[i] = btn;
			}
		}
	}
}

void Mouse::RemoveBtn(int btn)
{
	if (CheckIfBtnIsPressed(btn)) {
		for (int i = 0; i < MAX_MOUSE_PRESS; i++) {
			if (mouse_btns[i] == btn) {
				mouse_btns[i] = -1;
			}
		}
	}
}
