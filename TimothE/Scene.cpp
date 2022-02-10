#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>
#include "TextComponent.h"
#include "StreamFile.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Renderer2D.h"

#include "SubTexture2D.h"

int Scene::nextID = 0;
std::vector<GameObject*> Scene::_listOfGameObjects;
std::vector<GameObject*> Scene::_listOfDrawableGameObjects;

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

	Heap* gameObjectHeap = HeapManager::CreateHeap("GameObject", "Root");
	GameObject* _pTestObject = new(gameObjectHeap) GameObject("LENNA!", ObjectType::Player);
	_pTestObject->LoadTexture(ResourceManager::GetTexture("lenna"));
	_pTestObject->AddComponent(new BoxColliderComponent(_pTestObject));

	ResourceManager::InstantiateTexture("fish", new Texture2D("Fish.png"));

	//Order of transformations matters!!!!!
	//First we Translate
	//Then we rotate
	//Then finally scale
	_pTestObject->GetTransform()->SetPosition(0.0f, 0.0f);
	_pTestObject->GetTransform()->SetScale({0.2f, 0.2f});

	GameObject* _pTestObject2 = new GameObject("In World Object", ObjectType::Player);
	_pTestObject2->LoadTexture(ResourceManager::GetTexture("lenna"));
	_pTestObject2->AddComponent(new BoxColliderComponent(_pTestObject2));
	_pTestObject2->GetTransform()->SetPosition(550, 360);
	_pTestObject2->GetTransform()->SetScale({ 0.2f,0.2f });


	GameObject* _pButtonTestingObject = new GameObject("BUTTON", ObjectType::UI);
	_pButtonTestingObject->AddComponent(new Button(_pButtonTestingObject));
	_pButtonTestingObject->AddComponent(new BoxColliderComponent(_pButtonTestingObject));
	_pButtonTestingObject->AddComponent(new TextComponent(_pTestObject));
	_pButtonTestingObject->LoadTexture(ResourceManager::GetTexture("fish"));
	_pButtonTestingObject->SetShader("ui");
	_pButtonTestingObject->GetTransform()->SetPosition(0.0f, 0.0f);
	_pButtonTestingObject->GetTransform()->SetScale({ 0.2f, 0.2f });
	_pButtonTestingObject->SetType(ObjectType::UI);

	AddGameObject(_pTestObject);
	AddGameObject(_pTestObject2);
	AddGameObject(_pButtonTestingObject);

	GameObject* _pTextObj = new GameObject("TEXTOBJ", ObjectType::UI);
	_pTextObj->AddComponent(new TextComponent(_pTextObj));
	_pTextObj->SetType(ObjectType::UI);
	AddGameObject(_pTextObj);

	ResourceManager::InstantiateTexture("spritesheet", new Texture2D("testSheet.png"));

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

void Scene::EditorUpdate(float deltaTime)
{
	//Cycles through all gameobjects in the scene and calculates there transform.
	//Needed for the editor window to work smoothly
	for (GameObject* obj : _listOfGameObjects) {
		obj->GetTransform()->CalculateTransformMatrix();
		TextComponent* tc = obj->GetComponent<TextComponent>();
		if (tc != nullptr) {
			tc->OnStart();
			tc->OnUpdate(deltaTime);
		}
	}
}

void Scene::Update(float deltaTime)
{
	//Cycles through all gameobjects in the scene and updates them
	for (GameObject* obj : _listOfGameObjects)
	{
		obj->Update(deltaTime);
	}

	/////////////
	//TEST CODE//     BOX COLISSIONS
	/////////////

	if (_listOfGameObjects[0]->GetComponent<BoxColliderComponent>()->Intersects(_listOfGameObjects[1]->GetComponent<BoxColliderComponent>()->GetCollisionRect()))
	{
		std::cout << "Boxes are colliding" << std::endl;
	}

	glm::vec2 pos = _listOfGameObjects[1]->GetTransform()->GetPosition();
	if (Input::IsKeyDown(KEY_T))
	{
		_listOfGameObjects[1]->GetTransform()->SetPosition(pos.x + 0.5, pos.y );
	}
	if (Input::IsKeyDown(KEY_G))
	{
		_listOfGameObjects[1]->GetTransform()->SetPosition(pos.x - 0.5, pos.y );
	}

	//////////////////
	//END OF TEST CODE
	//////////////////
}

void Scene::RenderScene(Camera* cam)
{
	Renderer2D::BeginRender(cam);

	for (auto& obj : _listOfDrawableGameObjects) {
		//TODO: Text won't render here as it uses its own internal texture data. 
		Texture2D* objTex = obj->GetComponent<Texture2D>();

		if (objTex != nullptr) {
			if (obj->GetObjectType() == ObjectType::UI) {
				Renderer2D::DrawUIQuad(obj->GetTransform()->GetPosition(),
					obj->GetTransform()->GetScale(), obj->GetComponent<Texture2D>());
			}
			else {
				Renderer2D::DrawQuad(ConvertWorldToScreen(obj->GetTransform()->GetPosition()),
					obj->GetTransform()->GetScale(), objTex);
			}
		}
	}

	Renderer2D::EndRender();
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	//Searches for the desired object and deletes it if it is found
	_listOfGameObjects.erase(std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject));
	delete gameObject;
	gameObject = nullptr;
}

void Scene::AddedComponentHandler(GameObject* gameObject, Component* comp)
{
	//If this component is a graphics component
	if (comp->IsInCategory(Component::Graphics_Category)) {
		//If the Gameobject is not already in the drawables list
		if (std::find(_listOfDrawableGameObjects.begin(), _listOfDrawableGameObjects.end(), gameObject) == _listOfDrawableGameObjects.end()) {
			_listOfDrawableGameObjects.push_back(gameObject);
		}
	}
}

void Scene::RemoveComponentHandler(GameObject* gameObject, Component* comp)
{
	if (!comp->IsInCategory(Component::Graphics_Category)) return;

	//Get all components the gameobject has
	std::vector<Component*> goComps = gameObject->GetComponents();
	for (auto& c : goComps) {
		//if the current component is the one we are removing then go to next iteration
		if (c == comp) continue;

		//if the current component is a graphics category then return as the object does not need to be removed from drawables.
		if (c->IsInCategory(Component::Graphics_Category)) return;
	}

	//remove from drawables if all graphics components have been removed
	_listOfDrawableGameObjects.erase(std::find(_listOfDrawableGameObjects.begin(), _listOfDrawableGameObjects.end(), gameObject));
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
