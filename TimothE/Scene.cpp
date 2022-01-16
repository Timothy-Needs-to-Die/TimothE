#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>

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
	Texture2D* t = new Texture2D();
	t->Load("lenna3.jpg", "linear");

	static const GLfloat g_vertex_buffer_data[] =
	{
		//pos				//tex
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.5f, 1.0f
	};

	GameObject* _pTestObject = new GameObject("LENNA!", ObjectType::Player, t);
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
	//std::vector<GameObject*>::iterator pos = std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject);
	/*std::iter_swap(_listOfGameObjects.begin() + pos, _listOfGameObjects.end() - 1);
	_listOfGameObjects.pop_back();*/
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
		go->Read(stream);
		_listOfGameObjects[i] = go;
	}

}

void Scene::SaveScene(const std::string& filename)
{
	StreamFile stream;
	stream.OpenWrite(filename);

	//Writes the amount of game objects in the scene 
	WriteInt(stream, _listOfGameObjects.size());

	for (int i = 0; i < _listOfGameObjects.size(); ++i) {
		_listOfGameObjects[i]->Write(stream);
	}


}
