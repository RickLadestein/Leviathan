#include "Mouse.h"
namespace Leviathan::Input {
	Mouse::Mouse()
	{
		this->pos_x = 0;
		this->pos_y = 0;
		this->x_delta = 0;
		this->y_delta = 0;
		this->last_mode_update = 0;
		mouse_btns = new int[MAX_MOUSE_PRESS];
		for (int i = 0; i < MAX_MOUSE_PRESS; i++) {
			mouse_btns[i] = -1;
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
		switch (event->GetType()) {
		case Leviathan::Events::EventType::MouseMoveEvent:
		{
			Leviathan::Events::MouseMoveEvent* ev = dynamic_cast<Leviathan::Events::MouseMoveEvent*> (event);
			ev->GetPosition(&this->pos_x, &this->pos_y);
			ev->GetDelta(&this->x_delta, &this->y_delta);
		}
		break;
		case Leviathan::Events::EventType::MousePressEvent:
		{
			Leviathan::Events::MousePressEvent* ev = dynamic_cast<Leviathan::Events::MousePressEvent*> (event);
			this->AddBtn(ev->GetButton());
		}
		break;
		case Leviathan::Events::EventType::MouseReleaseEvent:
		{
			Leviathan::Events::MouseReleaseEvent* ev = dynamic_cast<Leviathan::Events::MouseReleaseEvent*> (event);
			this->RemoveBtn(ev->GetButton());
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
}
