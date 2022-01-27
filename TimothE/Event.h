#pragma once

#define BIT(x) (1 << x)

#include "pch.h"

//Events currently happen and then instantly get handled.
//No event queue system currently TODO: Implement a event queue?

//Describes the main event types, AppTick/Update/Render may not be used but the theory behind them is to use them to say when the game objects will be updated
enum class EventType {
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	//WINDOW EVENTS
	AppTick, AppUpdate, AppRender,											//APP EVENTS
	KeyPressed, KeyReleased,												//KEYBOARD EVENTS
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled		//MOUSE BUTTON EVENTS
};


//Using this system allows us to have events in categories so we could get all the input events or all of the mouse events etc.
//Essentially a trait we can give to each event
enum EventCategory {
	None = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1),
	EventCategoryKeyboard = BIT(2),
	EventCategoryMouse = BIT(3),
	EventCategoryMouseButton = BIT(4)
};

//Setup the pure virtual methods for each class. Using a macro reduces the amount of handwritten code. 
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
									virtual EventType GetEventType() const override { return GetStaticType();}\
									virtual const char* GetName() const override { return #type; }

	//Setup the GetCetegoryFlags method for each class. Using a macro reduces the amount of handwritten code.
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }

	//Base class for all events
class Event {
	friend class EventDispatcher;

public:
	//TODO: GetName GetCategoryFlags ToString could only be debug methods.

	//Pure virtual. Must be implemented
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;

	//This can be overridden to give actual information to the developer.
	virtual std::string ToString() const { return GetName(); }

	//Uses bitwise operator to see if it belongs in a certain category. 
	inline bool IsInCategory(EventCategory category) {
		return GetCategoryFlags() & category;
	}

protected:
	//Has this event been handled?
	//This will be useful for when a event only wants to be processed once
	bool _handled = false;
};

//A class that dispatches an event 
class EventDispatcher {
	//std::function that takes in a T reference. T could be WindowsResizeEvent or MousePressed etc.
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	EventDispatcher(Event& event) : _event(event) {

	}


	template<typename T>
	bool Dispatch(EventFn<T> func) {
		//Checks if the event we are trying to dispatch is the same as the passed type.
		if (_event.GetEventType() == T::GetStaticType()) {
			//if the event is the same type as the type we are dispatching with then it will call the function associated with this event.
			_event._handled = func(*(T*)&_event);
			return true;
		}
		return false;
	}

private:
	Event& _event;
};

//Exists for spdlog library. Just makes logging the events easier
inline std::ostream& operator<<(std::ostream& os, const Event& e) {
	return os << e.ToString();
}
