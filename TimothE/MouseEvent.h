#pragma once

#include "Event.h"

//Mouse moved event, says where the mouse currently is
class MouseMovedEvent : public Event {
public:
	MouseMovedEvent(float x, float y) : _mouseX(x), _mouseY(y) {}

	//Getters
	inline float GetX() const { return _mouseX; }
	inline float GetY() const { return _mouseY; }

	//Output debug information
	std::string ToString() const override {
		std::stringstream ss;
		ss << "MouseMovedEvent: " << _mouseX << ", " << _mouseY;
		return ss.str();
	}

	//Setting up the virtual methods
	EVENT_CLASS_TYPE(MouseMoved);
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float _mouseX, _mouseY;
};

//Mouse scroll event. Activated when scroll wheel is activated
class  MouseScrolledEvent : public Event {
public:
	MouseScrolledEvent(float xOffset, float yOffset) : _xOffset(xOffset), _yOffset(yOffset) {}

	//Getters
	inline float GetOffsetX() const { return _xOffset; }
	inline float GetOffsetY() const { return _yOffset; }

	//Debug Information
	std::string ToString() const override {
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << _xOffset << ", " << _yOffset;
		return ss.str();
	}

	//Setting up the virtual methods
	EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	//_xOffset. some mice have horizontal scrolling as well. Need to handle this in order to make sure there will be no crashes when dealing with one of these mice
	float _xOffset, _yOffset;
};

//Mouse Button Event. Any event that involves a button on the mouse
class  MouseButtonEvent : public Event {
public:
	inline int GetMouseButton() const { return _button; }

	//Setting up the virtual method
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
	MouseButtonEvent(int button) :_button(button) {}

	int _button;
};

//Mouse button pressed event, any time a button is clicked.
class  MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int button)
		: MouseButtonEvent(button) {}

	//Debug Information
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << _button;
		return ss.str();
	}

	//Setting up the virtual method
	EVENT_CLASS_TYPE(MouseButtonPressed)
};

//Mouse Button relased event, anytime a mouse button is released.
class  MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int button)
		: MouseButtonEvent(button) {}

	//Debug Information
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << _button;
		return ss.str();
	}

	//Setting up the virtual method
	EVENT_CLASS_TYPE(MouseButtonReleased)
};
