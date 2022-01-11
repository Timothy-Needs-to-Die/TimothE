#pragma once

#include "Event.h"


//Windows resize event. Called when the user changes screen size / resolution
class  WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int width, unsigned int height) : _width(width), _height(height) {
	}

	inline unsigned int GetWidth() const { return _width; }
	inline unsigned int GetHeight() const { return _height; }

	//Debug Information
	std::string ToString() const override {
		std::stringstream ss;
		ss << "WindowResizeEvent: " << _width << ", " << _height;
		return ss.str();
	}

	//Setting up virtual methods.
	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
	unsigned int _width, _height;
};

//Window Close Event. Called when the window is closed
class  WindowCloseEvent : public Event {
public:
	WindowCloseEvent() {}

	//Setting up virtual methods.
	EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


class  AppTickEvent : public Event {
	AppTickEvent() {}

	//Setting up virtual methods.
	EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class  AppUpdateEvent : public Event {
	AppUpdateEvent() {}

	//Setting up virtual methods.
	EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class  AppRenderEvent : public Event {
	AppRenderEvent() {}

	//Setting up virtual methods.
	EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
