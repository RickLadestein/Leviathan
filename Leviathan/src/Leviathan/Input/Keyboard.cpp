#include "Keyboard.h"

Keyboard::Keyboard()
{
	this->mode = KeyboardMode::INPUT;
	keys = new int[MAX_KEY_PRESSED];
	for (int i = 0; i < MAX_KEY_PRESSED; i++) {
		keys[i] = GLFW_KEY_UNKNOWN;
	}
}

Keyboard::~Keyboard()
{
	delete[] keys;
}

void Keyboard::AddKey(int key)
{
	if (!CheckIfKeyIsPresent(key)) {
		for (int i = 0; i < MAX_KEY_PRESSED; i++) {
			if (keys[i] == GLFW_KEY_UNKNOWN) {
				keys[i] = key;
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

void Keyboard::onKeyEvent(Event* ev)
{
	switch (ev->GetType()) {
	case EventType::KeyPressEvent:
	{
		KeyPressEvent* ptr = dynamic_cast<KeyPressEvent*>(ev);
		int key = ptr->key;
		AddKey(key);
	}
		break;
	case EventType::KeyReleaseEvent:
	{
		KeyReleaseEvent* ptr = dynamic_cast<KeyReleaseEvent*>(ev);
		int key = ptr->key;
		RemoveKey(key);
	}
		break;
	}
}
