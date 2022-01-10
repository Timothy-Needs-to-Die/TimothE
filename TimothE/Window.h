#pragma once

#include <GLFW/glfw3.h>
#include <GL/GL.h>

class Window
{
public:
	/// <summary>
	/// Constructor for creating a window. Using this creates a GLFWwindow object.
	/// </summary>
	/// <param name="width">The width of the window</param>
	/// <param name="height">The height of the window</param>
	/// <param name="name">The name of the window</param>
	Window(unsigned int width, unsigned int height, const char* name);

	//Gets the GLFWwindow associated with this Window class
	GLFWwindow* GetGLFWWindow() const { return _pWindow; }
private:
	//Creates a GLFWwindow with the passed in width, height and name.
	void CreateWindow(unsigned int width, unsigned int height, const char* name);

private:
	unsigned int _width, _height;
	const char* _pName;
	GLFWwindow* _pWindow;
};

