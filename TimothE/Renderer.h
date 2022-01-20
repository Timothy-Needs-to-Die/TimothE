#pragma once

#include <GL/glew.h>
#include "GameObject.h"
#include "Shader.h"
#include <iostream>
#include <vector>
#include "Texture2D.h"
#include <gtc/type_ptr.hpp>
#include "Camera.h"

class Renderer
{
public:
	static void Initialize();
	void RenderDrawables(vector<GameObject*> gameObjects, Camera* cam);
	void Render(GameObject* gameObject, Camera* cam);
};
