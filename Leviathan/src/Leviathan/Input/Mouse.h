#pragma once
#include "Leviathan/Event.h"
#include "GLFW/glfw3.h"
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
class Mouse {
public:
	Mouse();
	~Mouse();

	void GetMousePosition(double* x, double* y);
	void onEvent(Event* event);
private:
	double pos_x, pos_y;
	double x_delta, y_delta;
	int* mouse_btns;
	MouseInputMode mouseinputmode;
	MouseMode mousemode;
	bool CheckIfBtnIsPressed(int btn);
	void AddBtn(int btn);
	void RemoveBtn(int btn);

	friend class Window;
};