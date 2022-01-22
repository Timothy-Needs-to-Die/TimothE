#pragma once

#include "pch.h"

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

	//Sets an event callback for the window
	void SetEventCallback(const EventCallbackFn& callback);

	//Sets the background colour of the window
	void SetWindowColour(float r, float g, float b, float a);

	//Handles GLFW closing and termination behavior
	void DestroyWindow();

	//Creates a GLFWwindow with the passed in width, height and name.
	void CreateWindow();

	//Swaps the front and back buffers of the window
	void SwapBuffers();

	float GetHeight() const { return _windowData._height; }
	float GetWidth() const { return _windowData._width; }
private:


private:
	GLFWwindow* _pWindow;

	struct WindowData
	{
		std::string _title;
		unsigned int _width, _height;
		bool _vsync;
		EventCallbackFn _eventCallback;
	};

	WindowData _windowData;
};

