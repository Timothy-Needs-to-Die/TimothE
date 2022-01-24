#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>
#include "TextComponent.h"

#include "AddressTranslator.h"
#include "StreamFile.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Renderer2D.h"

int Scene::nextID = 0;
std::vector<GameObject*> Scene::_listOfGameObjects;

Shader* shader;
TextComponent* text;
Scene::Scene(std::string name)
{
	_listOfGameObjects.clear();

	_id = ++nextID;
	_name = name;

	/////////////
	//TEST CODE//
	/////////////
	GameObject* _pTestObject = new GameObject("LENNA!", ObjectType::Player);
	//_pTestObject->LoadTexture(ResourceManager::GetTexture("lenna"));

	ResourceManager::InstantiateTexture("fish", new Texture2D("Fish.png"));

	//Order of transformations matters!!!!!
	//First we Translate
	//Then we rotate
	//Then finally scale
	_pTestObject->GetTransform()->SetPosition(640, 360);

	GameObject* _pButtonTestingObject = new GameObject("BUTTON", ObjectType::UI);
	//_pButtonTestingObject->LoadTexture(ResourceManager::GetTexture("lenna"));
	_pTestObject->GetTransform()->Translate({ 100,100 });
	_pTestObject->GetTransform()->Scale({ 320,320 });

	_pButtonTestingObject->AddComponent(new Button(_pButtonTestingObject));
	_pButtonTestingObject->SetShader("ui");

	AddGameObject(_pTestObject);
	AddGameObject(_pButtonTestingObject);
	
	GameObject* _pTextObj = new GameObject("TEXTOBJ", ObjectType::UI);
	AddGameObject(_pTextObj);
	_pTextObj->AddComponent(new TextComponent(_pTextObj, "arial"));
	

	ResourceManager::InstantiateTexture("spritesheet", new Texture2D("testSheet.png"));

	unsigned int sheetWidth = 2560, sheetHeight = 1664;
	unsigned int spriteWidth = 128, spriteHeight = 128;
	unsigned int x = 10, y = 7;



	_uvSpriteCoords = new glm::vec2[4];
	_uvSpriteCoords[0] =  glm::vec2(((float)x * (float)spriteWidth) / (float)sheetWidth, ((float)y * (float)spriteHeight) / (float)sheetHeight );
	_uvSpriteCoords[1] =  glm::vec2((((float)x + 1) * (float)spriteWidth) / (float)sheetWidth, ((float)y * (float)spriteHeight) / (float)sheetHeight );
	_uvSpriteCoords[2] =  glm::vec2((((float)x + 1) * (float)spriteWidth) / (float)sheetWidth, (((float)y + 1) * (float)spriteHeight) / (float)sheetHeight );
	_uvSpriteCoords[3] =  glm::vec2(((float)x * (float)spriteWidth) / (float)sheetWidth, (((float)y + 1) * (float)spriteHeight) / (float)sheetHeight );
	std::cout << _uvSpriteCoords[0].x << std::endl;

	//////////////////
	//END OF TEST CODE
	//////////////////
}

Scene::~Scene()
{
	for (GameObject* obj : _listOfGameObjects)
	{
		delete(obj);
	}
}

void Scene::SceneStart()
{
	for (GameObject* obj : _listOfGameObjects) {
		obj->Start();
	}
}

void Scene::SceneEnd()
{
	for (GameObject* obj : _listOfGameObjects) {
		obj->Exit();
	}
}

void Scene::ScenePause()
{

}

void Scene::EditorUpdate()
{
	//Cycles through all gameobjects in the scene and calculates there transform.
	//Needed for the editor window to work smoothly
	for (GameObject* obj : _listOfGameObjects) {
		obj->GetTransform()->CalculateTransformMatrix();
	}
}

void Scene::Update(float deltaTime)
{
	//Cycles through all gameobjects in the scene and updates them
	for (GameObject* obj : _listOfGameObjects)
	{
		obj->Update(deltaTime);
	}
}

void Scene::RenderScene(Renderer* pRenderer, Camera* cam)
{
	//Renders the drawable objects
	//pRenderer->RenderDrawables(_listOfGameObjects, cam);

	


	Renderer2D::BeginRender(cam);
	Renderer2D::DrawQuad(glm::vec2(0.3f, 0.0f), glm::vec2(1.0f, 1.0f), ResourceManager::GetTexture("fish"));
	Renderer2D::DrawQuad(glm::vec2(0.7f, 0.0f), glm::vec2(0.5f, 0.5f), ResourceManager::GetTexture("fish"));
	Renderer2D::DrawQuad(glm::vec2(0.9f, 0.0f), glm::vec2(1.0f, 1.0f), ResourceManager::GetTexture("spritesheet"), _uvSpriteCoords);
	Renderer2D::DrawQuad(glm::vec2(-0.3f, 0.0f), glm::vec2(0.5f, 0.5f), ResourceManager::GetTexture("lenna"));
	Renderer2D::DrawQuad(glm::vec2(-0.7f, 0.0f), glm::vec2(0.5f, 0.5f), ResourceManager::GetTexture("fish"));
	Renderer2D::EndRender();

}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	//Searches for the desired object and deletes it if it is found
	_listOfGameObjects.erase(std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject));
	delete gameObject;
	gameObject = nullptr;
}

void Scene::LoadScene(const std::string& filename)
{
	//Clears the list (this is incase we are going from one scene to the next
	_listOfGameObjects.clear();

	//Creates a stream
	StreamFile stream;
	//Opens the stream for reading
	stream.OpenRead(filename);

	//recreates the list of gameobjects
	_listOfGameObjects = std::vector<GameObject*>();

	//Read in the amount of game objects in the scene
	int amountOfGo = ReadInt(stream);
	_listOfGameObjects.resize(amountOfGo);

	//Read in the information for each game object
	for (int i = 0; i < amountOfGo; ++i) {
		GameObject* go = new GameObject();
		go->LoadState(stream);
		_listOfGameObjects[i] = go;
	}

	stream.Close();
}

void Scene::SaveScene(const std::string& filename)
{
	//Creates a stream file object
	StreamFile stream;
	//Opens this stream for writing
	stream.OpenWrite(filename);

	//Writes the amount of game objects in the scene
	WriteInt(stream, _listOfGameObjects.size());

	//Cycles through each object and calls there save method
	for (int i = 0; i < _listOfGameObjects.size(); ++i) {
		_listOfGameObjects[i]->SaveState(stream);
	}

	//Closes the stream
	stream.Close();
}

GameObject* Scene::GetGameObjectByName(std::string name)
{
	//Cycles through all gameobjects in the scene
	for (GameObject* obj : _listOfGameObjects) {
		//if the gameobjects name matches the passed in one
		if (obj->GetName() == name) {
			//Return the object
			return obj;
		}
	}
	return nullptr;
}

GameObject* Scene::GetGameObjectByID(std::string id)
{
	//Cycles through all gameobjects in the scene
	for (GameObject* obj : _listOfGameObjects) {
		//if the ID matches
		if (obj->GetUID() == id) {
			//Returns the object
			return obj;
		}
	}

	//if no object is found with the passed in Id then return nullptr
	return nullptr;
}

GameObject* Scene::GetGameObjectByType(ObjectType type)
{
	//Cycles through all gameobjects in the scene
	for (GameObject* obj : _listOfGameObjects) {
		//Checks if the types match
		if (obj->GetType() == type) {
			//returns the object
			return obj;
		}
	}
	//returns nullptr if the object was not found
	return nullptr;
}

std::vector<GameObject*> Scene::GetGameObjectsByName(std::string name)
{
	//vector of gameobjects
	std::vector<GameObject*> list;
	//Cycles through all the gameobjects in the scene
	for (GameObject* obj : _listOfGameObjects) {
		//Checks if the names matchup
		if (obj->GetName() == name) {
			//Adds the object to the vector
			list.emplace_back(obj);
		}
	}

	//Returns the vector
	return list;
}

std::vector<GameObject*> Scene::GetGameObjectsByType(ObjectType type)
{
	//vector of gameobjects
	std::vector<GameObject*> list;
	//Cycles through all the gameobjects in the scene
	for (GameObject* obj : _listOfGameObjects) {
		//checks if the types match
		if (obj->GetType() == type) {
			//Adds the object to the vector
			list.emplace_back(obj);
		}
	}

	//Returns the vector
	return list;
}
