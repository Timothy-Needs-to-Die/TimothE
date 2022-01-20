#pragma once

#include <GL/glew.h>
#include "GameObject.h"
#include "Shader.h"
#include <iostream>
#include <vector>
#include "Texture2D.h"
#include <gtc/type_ptr.hpp>

class Renderer
{
public:
	Renderer() : _UID(UID::GenerateUID()) { };

	void RenderDrawables(vector<GameObject*> gameObjects);
	void Render(GameObject* gameObject);
private:
	std::string _UID;
};
