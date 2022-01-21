#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>

#include "AddressTranslator.h"
#include "StreamFile.h"
#include "Button.h"
#include "ResourceManager.h"

int Scene::nextID = 0;

Scene::Scene(string name)
{
	_id = ++nextID;
	_name = name;

	/////////////
	//TEST CODE//
	/////////////
	GameObject* _pTestObject = new GameObject("LENNA!", ObjectType::Player);
	_pTestObject->LoadTexture(ResourceManager::GetTexture("lenna"));

	//Orde of transformations matters!!!!!
	//First we Translate
	//Then we rotate
	//Then finally scale
	_pTestObject->GetTransform()->SetPosition(640, 360);

	GameObject* _pButtonTestingObject = new GameObject("BUTTON", ObjectType::UI);
	_pButtonTestingObject->LoadTexture(ResourceManager::GetTexture("lenna"));
	_pTestObject->GetTransform()->Translate({ 100,100 });
	_pTestObject->GetTransform()->Scale({ 320,320 });

	_pButtonTestingObject->AddComponent(new Button(_pButtonTestingObject));
	_pButtonTestingObject->SetShader("ui");

	AddGameObject(_pTestObject);
	AddGameObject(_pButtonTestingObject);
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

void Scene::RenderScene(Renderer* pRenderer, Camera* cam)
{
	pRenderer->RenderDrawables(_listOfGameObjects, cam);
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
