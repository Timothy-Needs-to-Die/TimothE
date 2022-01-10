#include "Window.h"


#include <iostream>

Window::Window(unsigned int width, unsigned int height, const char* name)
	: _width(width), _height(height), _pName(name) //Initialize Member variables
{
	CreateWindow(_width, _height, _pName);
}

void Window::CreateWindow(unsigned int width, unsigned int height, const char* name)
{
	//Create and assign the GLFWwindow object
	_pWindow = glfwCreateWindow(width, height, name, nullptr, nullptr);
	
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
}
