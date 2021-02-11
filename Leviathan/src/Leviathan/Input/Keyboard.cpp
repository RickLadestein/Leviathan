#include "Keyboard.h"
#include "GLFW/glfw3.h"
namespace Leviathan::Input {
	Keyboard::Keyboard()
	{
		this->mode = KeyboardMode::INPUT;
		for (size_t i = 0; i < MAX_KEY_PRESSED; i++) {
			keys[i] = KeyCode::KEY_UNKNOWN;
		}
	}


	void Keyboard::AddKey(KeyCode key)
	{
		if (!CheckIfKeyIsPresent(key)) {
			for (size_t i = 0; i < MAX_KEY_PRESSED; i++) {
				if (keys[i] == KeyCode::KEY_UNKNOWN) {
					keys[i] = key;
					return;
				}
			}
		}
	}

	void Keyboard::RemoveKey(KeyCode key)
	{
		if (CheckIfKeyIsPresent(key)) {
			for (int i = 0; i < MAX_KEY_PRESSED; i++) {
				if (keys[i] == key) {
					keys[i] = KeyCode::KEY_UNKNOWN;
				}
			}
		}
	}

	bool Keyboard::CheckIfKeyIsPresent(KeyCode key)
	{
		for (int i = 0; i < MAX_KEY_PRESSED; i++) {
			if (keys[i] == key) {
				return true;
			}
		}
		return false;
	}

	void Keyboard::GetPressedKeys(std::vector<KeyCode>* keys)
	{
		if (keys != nullptr) {
			for (int i = 0; i < MAX_KEY_PRESSED; i++) {
				if (this->keys[i] != KeyCode::KEY_UNKNOWN)
					keys->push_back(this->keys[i]);
			}
		}
	}

	void Keyboard::onKeyEvent(Leviathan::Events::Event* ev)
	{
		switch (ev->GetEventType()) {
		case Leviathan::Events::EventType::KeyPress:
		{
			Leviathan::Events::KeyPressEvent* ptr = dynamic_cast<Leviathan::Events::KeyPressEvent*>(ev);
			KeyCode key = ptr->GetKey();
			AddKey(key);
		}
		break;
		case Leviathan::Events::EventType::KeyRelease:
		{
			Leviathan::Events::KeyReleaseEvent* ptr = dynamic_cast<Leviathan::Events::KeyReleaseEvent*>(ev);
			KeyCode key = ptr->GetKey();
			RemoveKey(key);
		}
		break;
		}
	}
}
