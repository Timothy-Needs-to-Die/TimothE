#pragma once

#include "Event.h"

//Key Events are any events related to the keyboard. All key events need to take note of the key code.

class KeyEvent : public Event {
public:
	//Gets the keycode
	inline int GetKeyCode() const { return _keyCode; }

	//Sets the categories for all KeyEvents
	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	KeyEvent(int keycode)
		: _keyCode(keycode) {}

	//Stores the key code
	int _keyCode;
};

//Pressing a key down event.
class KeyPressedEvent : public KeyEvent {
public:
	KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {}

	inline int GetRepeatCount() const { return _repeatCount; }

	//Output debug information
	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << _keyCode << " (" << _repeatCount << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)
private:
	int _repeatCount; //Stores the amount of times the key has been held down. 
};

//Key released event
class KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

	//Output debug information
	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << _keyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};
