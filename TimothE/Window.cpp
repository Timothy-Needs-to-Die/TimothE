#include "Window.h"


#include <iostream>

void Window::Init(unsigned int width, unsigned int height, const char* name)
{
	_windowData = WindowData();
	_windowData._width = width;
	_windowData._height = height;
	_windowData._title = name;
}

GLFWwindow* Window::GetGLFWWindow()
{
	return _pWindow;
}

glm::vec2 Window::GetWindowSize()
{
	return glm::vec2(_windowData._width, _windowData._height);
}

glm::vec2 Window::GetHalfWindowSize()
{
	return glm::vec2(_windowData._width / 2.0f, _windowData._height / 2.0f);
}

float Window::GetAspectRatio()
{
	return  (float)_windowData._width / (float)_windowData._height;
}

//Sets an event callback for the window
void Window::SetEventCallback(const EventCallbackFn& callback)
{
	_windowData._eventCallback = callback;
}

void Window::SetWindowColour(float r, float g, float b, float a)
{
	//Sets this to be the current window being edited
	glfwMakeContextCurrent(_pWindow);

	//Sets background colour and clears the colour buffer bit
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::DestroyWindow()
{
	glfwDestroyWindow(_pWindow);
}

void Window::CreateWindow()
{
	//Create and assign the GLFWwindow object
	_pWindow = glfwCreateWindow(_windowData._width, _windowData._height, _windowData._title.c_str(), nullptr, nullptr);

	//Makes this current window the context (current one to be edited
	glfwMakeContextCurrent(_pWindow);
	if (!_pWindow)
	{
		//Output an error and terminate GLFW
		std::cout << "Error creating window" << std::endl;
		glfwTerminate();
	}

	//Syncs to monitor refresh rate
	//1: Vsync. 0: No Vsync
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(_pWindow, &_windowData);

	//Sets the callback for resizing the window
	glfwSetWindowSizeCallback(_pWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data._width = width;
			data._height = height;

			WindowResizeEvent event(width, height);
			data._eventCallback(event);
		});

	//Sets the callback for closing a window
	glfwSetWindowCloseCallback(_pWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data._eventCallback(event);
		});

	//Sets the callback for pressing a key
	glfwSetKeyCallback(_pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data._eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data._eventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data._eventCallback(event);
				break;
			}
			}
		});

	//Sets the callback for pressing a mouse button
	glfwSetMouseButtonCallback(_pWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data._eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data._eventCallback(event);
				break;
			}
			}
		});

	//Sets the callback for scrolling the mouse wheel
	glfwSetScrollCallback(_pWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data._eventCallback(event);
		});

	//Sets the callback for when the mouse position changes
	glfwSetCursorPosCallback(_pWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data._eventCallback(event);
		});
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(_pWindow);
}

float Window::GetHeight()
{
	return _windowData._height;
}

float Window::GetWidth()
{
	return _windowData._width;
}

GLFWwindow* Window::_pWindow;

Window::WindowData Window::_windowData;
