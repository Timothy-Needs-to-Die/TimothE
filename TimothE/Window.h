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

	static void Init(unsigned int width, unsigned int height, const char* name);

	//Gets the GLFWwindow associated with this Window class
	static GLFWwindow* GetGLFWWindow() { return _pWindow; }

	static glm::vec2 GetWindowSize() { glm::vec2(_windowData._width, _windowData._height); }
	static glm::vec2 GetHalfWindowSize() { glm::vec2(_windowData._width / 2.0f, _windowData._height / 2.0f); }

	static float GetAspectRatio() {return  _windowData._width / _windowData._height; }

	//Sets an event callback for the window
	static void SetEventCallback(const EventCallbackFn& callback);

	//Sets the background colour of the window
	static void SetWindowColour(float r, float g, float b, float a);

	//Handles GLFW closing and termination behavior
	static void DestroyWindow();

	//Creates a GLFWwindow with the passed in width, height and name.
	static void CreateWindow();

	//Swaps the front and back buffers of the window
	static void SwapBuffers();

	static float GetHeight() { return _windowData._height; }
	static float GetWidth() { return _windowData._width; }
private:


private:
	static GLFWwindow* _pWindow;

	struct WindowData
	{
		std::string _title;
		unsigned int _width, _height;
		bool _vsync;
		EventCallbackFn _eventCallback;
	};

	static WindowData _windowData;
};

