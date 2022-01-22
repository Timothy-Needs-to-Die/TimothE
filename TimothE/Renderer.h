#pragma once

#include "pch.h"

#include "GameObject.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"

class Renderer
{
public:
	//Generates a uid for the renderer
	Renderer() : _UID(UID::GenerateUID()) { };

	//Renders drawables for the scene from a particular camera
	void RenderDrawables(vector<GameObject*> gameObjects, Camera* cam);
	void Render(GameObject* gameObject, Camera* cam);
private:
	//Stores the UID
	std::string _UID;
};
