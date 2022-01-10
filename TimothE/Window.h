#pragma once

#include <GLFW/glfw3.h>
#include <GL/GL.h>

#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

#include "Event.h"

#include "ApplicationEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	/// <summary>
	/// Constructor for creating a window.
	/// </summary>
	/// <param name="width">The width of the window</param>
	/// <param name="height">The height of the window</param>
	/// <param name="name">The name of the window</param>
	Window(unsigned int width, unsigned int height, const char* name);

	//Gets the GLFWwindow associated with this Window class
	GLFWwindow* GetGLFWWindow() const { return _pWindow; }

	void SetEventCallback(const EventCallbackFn& callback);

	//Creates a GLFWwindow with the passed in width, height and name.
	void CreateWindow();
private:


private:
	unsigned int _width, _height;
	const char* _pName;
	GLFWwindow* _pWindow;

	EventCallbackFn _callback;

	struct WindowData
	{
		std::string _title;
		unsigned int _width, _height;
		bool _vsync;
		EventCallbackFn _eventCallback;
	};

	WindowData _windowData;
};

