#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>

#include "GameObject.h"

class Graphics
{
public:
	void Initialize();
	void Render(GLFWwindow* window, GameObject* gameObject);
	void BindShader(unsigned int vertexShader);
private:
};

#endif