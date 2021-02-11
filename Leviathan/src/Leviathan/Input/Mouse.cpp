#include "Mouse.h"
namespace Leviathan::Input {
	Mouse::Mouse()
	{
		this->pos_x = 0;
		this->pos_y = 0;
		this->x_delta = 0;
		this->y_delta = 0;
		this->last_mode_update = 0;
		for (size_t i = 0; i < MAX_MOUSE_PRESS; i++) {
			mouse_btns[i] = MouseButton::BTN_UNKNOWN;
		}
		this->mouseinputmode = MouseInputMode::DEFAULT;
		this->mousemode = MouseMode::VISIBLE;
	}

	void Mouse::GetMousePosition(double* x, double* y)
	{
		*x = this->pos_x;
		*y = this->pos_y;
	}

	void Mouse::onEvent(Leviathan::Events::Event* event)
	{
		switch (event->GetEventType()) {
		case Leviathan::Events::EventType::MouseMove:
		{
			Leviathan::Events::MouseMoveEvent* ev = dynamic_cast<Leviathan::Events::MouseMoveEvent*> (event);
			ev->GetPosition(&this->pos_x, &this->pos_y);
			ev->GetDelta(&this->x_delta, &this->y_delta);
		}
		break;
		case Leviathan::Events::EventType::MousePress:
		{
			Leviathan::Events::MousePressEvent* ev = dynamic_cast<Leviathan::Events::MousePressEvent*> (event);
			MouseButton btn = ev->GetButton();
			this->AddBtn(btn);
		}
		break;
		case Leviathan::Events::EventType::MouseRelease:
		{
			Leviathan::Events::MouseReleaseEvent* ev = dynamic_cast<Leviathan::Events::MouseReleaseEvent*> (event);
			MouseButton _btn = ev->GetButton();
			this->RemoveBtn(_btn);
		}
		break;
		}
	}

	bool Mouse::CheckIfBtnIsPressed(MouseButton btn)
	{
		for (int i = 0; i < MAX_MOUSE_PRESS; i++) {
			if (mouse_btns[i] == btn) {
				return true;
			}
		}
		return false;
	}

	void Mouse::AddBtn(MouseButton btn)
	{
		if (!CheckIfBtnIsPressed(btn)) {
			for (int i = 0; i < MAX_MOUSE_PRESS; i++) {
				if (mouse_btns[i] == MouseButton::BTN_UNKNOWN) {
					mouse_btns[i] = btn;
				}
			}
		}
	}

	void Mouse::RemoveBtn(MouseButton btn)
	{
		if (CheckIfBtnIsPressed(btn)) {
			for (int i = 0; i < MAX_MOUSE_PRESS; i++) {
				if (mouse_btns[i] == btn) {
					mouse_btns[i] = MouseButton::BTN_UNKNOWN;
				}
			}
		}
	}
}
