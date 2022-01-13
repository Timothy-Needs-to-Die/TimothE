#include "Scene.h"

int Scene::nextID = 0;

Scene::Scene(string name)
{
	_id = ++nextID;
	_name = name;
	//AddGameObject(new GameObject("Test object", ObjectType::Player, NULL));
}

Scene::~Scene()
{
	for (GameObject* obj : _listOfGameObjects)
	{
		delete(obj);
	}
}

void Scene::Update(float deltaTime)
{
	for (GameObject* obj : _listOfGameObjects)
	{
		obj->Update(deltaTime);
	}
}

void Scene::RenderScene(GLFWwindow* pWindow, Graphics* pGraphics)
{
	for (auto const& object : _listOfGameObjects)
		pGraphics->Render(pWindow, object);
}
