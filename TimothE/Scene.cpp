#include "Scene.h"
#include <algorithm>

int Scene::nextID = 0;

Scene::Scene(string name)
{
	_id = ++nextID;
	_name = name;
	//AddGameObject(new GameObject("Test object", ObjectType::Player, (Texture2D*)nullptr));
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

void Scene::RemoveGameObject(GameObject* gameObject)
{
	_listOfGameObjects.erase(std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject));
	//std::vector<GameObject*>::iterator pos = std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject);
	/*std::iter_swap(_listOfGameObjects.begin() + pos, _listOfGameObjects.end() - 1);
	_listOfGameObjects.pop_back();*/
}
