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
	static void Initialize();
	void RenderDrawables(vector<GameObject*> gameObjects);
	void Render(GameObject* gameObject);
};
