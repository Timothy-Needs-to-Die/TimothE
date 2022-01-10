#pragma once

#include <GLFW/glfw3.h>
#include <GL/GL.h>

class Window
{
public:
	Window(unsigned int width, unsigned int height, const char* name);

private:
	void CreateWindow(unsigned int width, unsigned int height, const char* name);

private:
	unsigned int _width, _height;
	const char* _pName;
	GLFWwindow* _pWindow;
};

