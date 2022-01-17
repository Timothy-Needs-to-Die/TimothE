#pragma once

#include "GameObject.h"
#include "Shader.h"
#include <iostream>
#include <vector>

class Renderer
{
public:
	static void Initialize();
	void RenderDrawables(vector<GameObject*> gameObjects);
	void Render(GameObject* gameObject);
private:
	std::string _UID = UID::GenerateUID();
};
