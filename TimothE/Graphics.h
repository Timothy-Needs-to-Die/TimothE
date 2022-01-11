#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GameObject.h"
#include "Shader.h"

class Graphics
{
public:
	void Initialize();
	void Render(GLFWwindow* window, GameObject* gameObject);
private:
	Shader* _pShader;
};
