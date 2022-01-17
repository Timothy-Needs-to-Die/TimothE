#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>
#include "Text.h"
int Scene::nextID = 0;

Shader* shader;
Text* text;
Scene::Scene(string name)
{
	_id = ++nextID;
	_name = name;

	/////////////
	//TEST CODE//
	/////////////
	Texture2D* t = new Texture2D();
	t->Load("lenna4.jpg");

	
	shader = new Shader("fbVert.vs", "fbFrag.fs");

	static const GLfloat g_vertex_buffer_data[] =
	{
		//pos				//tex
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.5f, 1.0f
	};

	GameObject* _pTestObject = new GameObject("LENNA!", ObjectType::Player, t);
	_pTestObject->SetShader(shader->GetProgramID());

	AddGameObject(_pTestObject);

	shader = new Shader("txtVert.vs", "txtFrag.fs");
	
	text = new Text();

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
	text->RenderText(*shader, "Wacky Text", 10.0f, 30.0f, 1.0f, glm::vec3(0.2, 1.0f, 1.0f));
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	_listOfGameObjects.erase(std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject));
	//std::vector<GameObject*>::iterator pos = std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject);
	/*std::iter_swap(_listOfGameObjects.begin() + pos, _listOfGameObjects.end() - 1);
	_listOfGameObjects.pop_back();*/
}
