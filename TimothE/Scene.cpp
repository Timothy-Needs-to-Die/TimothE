#include "Scene.h"

Scene::Scene(string name)
{
	_id = ++nextID;
	_name = name;
}

Scene::~Scene()
{
}

void Scene::RenderScene(GLFWwindow* pWindow, Graphics* pGraphics)
{
	for (auto const& object : _listOfGameObjects)
		pGraphics->Render(pWindow, object);
}
