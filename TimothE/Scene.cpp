#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>
#include "Button.h"

int Scene::nextID = 0;

Scene::Scene(string name)
{
	_id = ++nextID;
	_name = name;

	/////////////
	//TEST CODE//
	/////////////
	/*Texture2D* t = new Texture2D();
	t->Load("lenna3.jpg", "linear");*/

	Shader* shader;
	shader = new Shader("fbVert.vs", "fbFrag.fs");

	//GameObject* _pTestObject = new GameObject("LENNA!", ObjectType::Player);
	//_pTestObject->LoadTexture("lenna3.jpg", "linear");

	Button* pButton = new Button("TestButton", 100, 100);

	AddGameObject(pButton);
	//AddGameObject(_pTestObject);
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

void Scene::RenderScene(Renderer* pRenderer)
{
	pRenderer->RenderDrawables(_listOfGameObjects);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	_listOfGameObjects.erase(std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject));
	/*int index = std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject) - _listOfGameObjects.begin();
	std::iter_swap(_listOfGameObjects.begin() + index, _listOfGameObjects.end() - 1);
	_listOfGameObjects.pop_back();*/
	delete gameObject;
}
