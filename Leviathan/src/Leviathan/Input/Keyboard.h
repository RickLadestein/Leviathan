#pragma once
#include "Leviathan/Core/Event.h"
#include "InputCodes.h"
#include <array>

#define MAX_KEY_PRESSED 5

namespace Leviathan::Input {
	
	/// <summary>
	/// Enum specifying keyboard mode
	/// </summary>
	enum class KeyboardMode {
		INPUT,
		TYPING
	};

	

	class Keyboard {
	public:
		Keyboard();
		~Keyboard() = default;

		inline void SetKeyboardMode(KeyboardMode mode) { this->mode = mode; };
		inline bool IsKeyPressed(KeyCode key) { return CheckIfKeyIsPresent(key); };
		void GetPressedKeys(std::vector<KeyCode>* keys);
		inline const KeyboardMode GetKeyboardMode() { return this->mode; };
		void onKeyEvent(Leviathan::Events::Event* ev);
	private:
		std::array<KeyCode, MAX_KEY_PRESSED> keys;
		KeyboardMode mode;
		void AddKey(KeyCode key);
		void RemoveKey(KeyCode key);
		bool CheckIfKeyIsPresent(KeyCode key);
	};

	
}

