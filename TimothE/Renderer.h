#pragma once

#include "GameObject.h"
#include "Shader.h"
#include <iostream>
#include <vector>

class Renderer
{
public:
	void Initialize();
	void RenderDrawables(vector<GameObject*> gameObjects);
public:
	Shader* _pShader;
private:
	void Render(GameObject* gameObject);
};
