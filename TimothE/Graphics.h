#pragma once

#include "GameObject.h"
#include <GLFW\glfw3.h>

class Graphics
{
public:
	void Render(GLFWwindow* window, GameObject* gameObject);
};