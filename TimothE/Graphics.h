#pragma once

#include "GameObject.h"
#include "Shader.h"

#include <iostream>
#include <vector>

class Graphics
{
public:
	void Initialize();
	void Render(vector<GameObject*> gameObjects);
public:
	Shader* _pShader;
};
