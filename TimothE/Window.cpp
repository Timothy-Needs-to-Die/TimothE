#include "Window.h"


#include <iostream>

Window::Window(unsigned int width, unsigned int height, const char* name)
	: _width(width), _height(height), _pName(name)
{
	CreateWindow(_width, _height, _pName);
}

void Window::CreateWindow(unsigned int width, unsigned int height, const char* name)
{
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		std::cout << "Error creating window" << std::endl;
		glfwTerminate();
	}

	//Syncs to monitor refresh rate
	glfwSwapInterval(1);
}
