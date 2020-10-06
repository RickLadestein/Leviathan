#pragma once
#include "Leviathan/Core/Event.h"
#include "Leviathan/Data/Object.h"
#include "GLFW/glfw3.h"

namespace Leviathan::Input {
#define MAX_MOUSE_PRESS 5

	enum class MouseInputMode {
		DEFAULT,
		RAW
	};

	enum class MouseMode {
		VISIBLE,
		INVISIBLE,
		CENTERED
	};
	class Mouse : public Object {
	public:
		Mouse();
		~Mouse() { delete this->mouse_btns; }

		void GetMousePosition(double* x, double* y);
		void onEvent(Leviathan::Events::Event* event);
		inline MouseMode GetMouseMode() { return this->mousemode; }
		inline void SetMouseMode(MouseMode mode) { this->mousemode = mode; }

		inline MouseInputMode GetMouseInputMode() { return this->mouseinputmode; }
		inline void SetMouseInputMode(MouseInputMode mode) { this->mouseinputmode = mode; }

		inline void SetLastMouseUpdate(double time) { this->last_mode_update = time; }
		inline double GetLastMouseUpdate() { return this->last_mode_update; }
	private:
		double pos_x, pos_y;
		double x_delta, y_delta;
		int* mouse_btns;
		double last_mode_update;
		MouseInputMode mouseinputmode;
		MouseMode mousemode;
		bool CheckIfBtnIsPressed(int btn);
		void AddBtn(int btn);
		void RemoveBtn(int btn);

		friend class Window;
	};
}