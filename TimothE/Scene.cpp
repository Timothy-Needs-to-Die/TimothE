#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>

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

	static const GLfloat g_vertex_buffer_data[] =
	{
		//pos				//tex
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.5f, 1.0f
	};

	GameObject* _pTestObject = new GameObject("LENNA!", ObjectType::Player);
	_pTestObject->LoadTexture("lenna3.jpg", "linear");
	//VERTEX DATA NEEDS TO BE STORED IN GAMEOBJECT

	AddGameObject(_pTestObject);
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
