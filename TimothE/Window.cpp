#include "Window.h"


#include <iostream>

Window::Window(unsigned int width, unsigned int height, const char* name)
	: _width(width), _height(height), _pName(name) //Initialize Member variables
{
}

void Window::SetEventCallback(const EventCallbackFn& callback)
{
	_callback = callback;
	_windowData._eventCallback = callback;
}

void Window::CreateWindow()
{
	_windowData._width = _width;
	_windowData._height = _height;
	_windowData._title = _pName;
	//Create and assign the GLFWwindow object
	_pWindow = glfwCreateWindow(_width, _height, _pName, nullptr, nullptr);

	//Makes this current window the context (current one to be edited
	glfwMakeContextCurrent(_pWindow);
	if (!_pWindow)
	{
		//Output an error and terminate GLFW
		std::cout << "Error creating window" << std::endl;
		glfwTerminate();
	}

	//Syncs to monitor refresh rate
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(_pWindow, &_windowData);

	glfwSetWindowSizeCallback(_pWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data._width = width;
			data._height = height;

			WindowResizeEvent event(width, height);
			data._eventCallback(event);
		});

	glfwSetWindowCloseCallback(_pWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data._eventCallback(event);
		});

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

	glfwSetScrollCallback(_pWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data._eventCallback(event);
		});

	glfwSetCursorPosCallback(_pWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data._eventCallback(event);
		});
}
