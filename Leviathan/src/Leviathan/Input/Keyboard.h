#pragma once
#include "Leviathan/Core/Event.h"
#include "Leviathan/Data/Object.h"
#include "GLFW/glfw3.h"

#define MAX_KEY_PRESSED 5

namespace Leviathan::Input {
	enum class KeyboardMode {
		INPUT,
		TYPING
	};
	class Keyboard : public Object {
	public:
		Keyboard();
		~Keyboard() { delete this->keys; }

		inline void SetKeyboardMode(KeyboardMode mode) { this->mode = mode; };
		inline bool IsKeyPressed(int key) { return CheckIfKeyIsPresent(key); };
		void GetPressedKeys(std::vector<int>* keys);
		inline const KeyboardMode GetKeyboardMode() { return this->mode; };
		void onKeyEvent(Leviathan::Events::Event* ev);
	private:
		int* keys;
		KeyboardMode mode;
		void AddKey(int key);
		void RemoveKey(int key);
		bool CheckIfKeyIsPresent(int key);
	};
}