#pragma once

#include "GameObject.h"
#include "Shader.h"

#include <iostream>

class Graphics
{
public:
	void Initialize();
	void Render(GLFWwindow* window, GameObject* gameObject);
public:
	Shader* _pShader;
};
