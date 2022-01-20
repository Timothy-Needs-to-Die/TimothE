#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>
#include "TextComponent.h"
#include "Button.h"

#include "AddressTranslator.h"
#include "StreamFile.h"

int Scene::nextID = 0;

Shader* shader;
TextComponent* text;
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
	_pTestObject->LoadTexture("lenna3.jpg");

	//Orde of transformations matters!!!!!
	//First we Translate
	//Then we rotate
	//Then finally scale
	_pTestObject->GetTransform()->Translate({ 100,100 });
	_pTestObject->GetTransform()->Scale({ 320,320 });

	Button* pButton = new Button("TestButton", 32, 32);
	pButton->LoadTexture("lenna3.jpg");

	AddGameObject(pButton);
	AddGameObject(_pTestObject);

	shader = new Shader("txtVert.vs", "txtFrag.fs");
	
	text = new TextComponent("arial");

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
	text->RenderText(*shader, "lenna\nfopen", 10.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.2f, 1.0f));
	text->RenderText(*shader, "Wacky\nWacky", 400.0f, 200.0f, 2.0f, glm::vec3(1.0f, 0.2, 0.2f));
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
