#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>
#include "Button.h"
#include "AddressTranslator.h"
#include "StreamFile.h"

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

	GameObject* _pTestObject = new GameObject("LENNA!", ObjectType::Player);
	_pTestObject->LoadTexture("lenna3.jpg", "linear");
	//_pTestObject->AddComponent<BoxColliderComponent>(new BoxColliderComponent());

	//Orde of transformations matters!!!!!
	//First we Translate
	//Then we rotate
	//Then finally scale
	_pTestObject->GetTransform()->Translate({ 100,100 });
	_pTestObject->GetTransform()->Scale({ 32,32 });

	Button* pButton = new Button("TestButton", 32, 32);
	pButton->LoadTexture("lenna3.jpg", "linear");

	AddGameObject(pButton);
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
	delete gameObject;
}

void Scene::LoadScene(const std::string& filename)
{
	StreamFile stream;
	stream.OpenRead(filename);

	_listOfGameObjects = std::vector<GameObject*>();

	//Read in the amount of gameobjects in the scene
	int amountOfGo = ReadInt(stream);
	_listOfGameObjects.resize(amountOfGo);

	//Read in the information for each gameobject
	for (int i = 0; i < amountOfGo; ++i) {
		GameObject* go = new GameObject();
		go->LoadState(stream);
		_listOfGameObjects[i] = go;
	}

	stream.Close();
}

void Scene::SaveScene(const std::string& filename)
{
	StreamFile stream;
	stream.OpenWrite(filename);

	//Writes the amount of game objects in the scene
	WriteInt(stream, _listOfGameObjects.size());

	for (int i = 0; i < _listOfGameObjects.size(); ++i) {
		_listOfGameObjects[i]->SaveState(stream);
	}

	stream.Close();
}
