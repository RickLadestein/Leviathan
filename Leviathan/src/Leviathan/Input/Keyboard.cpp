#include "Keyboard.h"
namespace Leviathan::Input {
	Keyboard::Keyboard()
	{
		this->mode = KeyboardMode::INPUT;
		keys = new int[MAX_KEY_PRESSED];
		for (int i = 0; i < MAX_KEY_PRESSED; i++) {
			keys[i] = GLFW_KEY_UNKNOWN;
		}
	}


	void Keyboard::AddKey(int key)
	{
		if (!CheckIfKeyIsPresent(key)) {
			for (int i = 0; i < MAX_KEY_PRESSED; i++) {
				if (keys[i] == GLFW_KEY_UNKNOWN) {
					keys[i] = key;
					return;
				}
			}
		}
	}

	void Keyboard::RemoveKey(int key)
	{
		if (CheckIfKeyIsPresent(key)) {
			for (int i = 0; i < MAX_KEY_PRESSED; i++) {
				if (keys[i] == key) {
					keys[i] = GLFW_KEY_UNKNOWN;
				}
			}
		}
	}

	bool Keyboard::CheckIfKeyIsPresent(int key)
	{
		for (int i = 0; i < MAX_KEY_PRESSED; i++) {
			if (keys[i] == key) {
				return true;
			}
		}
		return false;
	}

	void Keyboard::GetPressedKeys(std::vector<int>* keys)
	{
		if (keys != nullptr) {
			for (int i = 0; i < MAX_KEY_PRESSED; i++) {
				if (this->keys[i] != GLFW_KEY_UNKNOWN)
					keys->push_back(this->keys[i]);
			}
		}
	}

	void Keyboard::onKeyEvent(Leviathan::Events::Event* ev)
	{
		switch (ev->GetType()) {
		case Leviathan::Events::EventType::KeyPressEvent:
		{
			Leviathan::Events::KeyPressEvent* ptr = dynamic_cast<Leviathan::Events::KeyPressEvent*>(ev);
			int key = ptr->GetKey();
			AddKey(key);
		}
		break;
		case Leviathan::Events::EventType::KeyReleaseEvent:
		{
			Leviathan::Events::KeyReleaseEvent* ptr = dynamic_cast<Leviathan::Events::KeyReleaseEvent*>(ev);
			int key = ptr->GetKey();
			RemoveKey(key);
		}
		break;
		}
	}
}
