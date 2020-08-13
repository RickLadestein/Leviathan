#pragma once
#include "Leviathan/Event.h"
#include "GLFW/glfw3.h"
#define MAX_KEY_PRESSED 5

enum class KeyboardMode {
	INPUT,
	TYPING
};
class Keyboard {
public:
	Keyboard();
	~Keyboard();

	inline void SetKeyboardMode(KeyboardMode mode) { this->mode = mode; };
	inline bool IsKeyPressed(int key) { return CheckIfKeyIsPresent(key); };
	inline const KeyboardMode GetKeyboardMode() { return this->mode; };
	void onKeyEvent(Event* ev);
private:
	int* keys;
	KeyboardMode mode;
	void AddKey(int key);
	void RemoveKey(int key);
	bool CheckIfKeyIsPresent(int key);
};