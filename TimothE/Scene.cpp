#include "Texture2D.h"
#include "Scene.h"
#include <algorithm>
#include "TextComponent.h"
#include "StreamFile.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Core/Graphics/Renderer2D.h"

#include "Core/Graphics/SubTexture2D.h"
#include "PlayerInputComponent.h"
#include "SpriteComponent.h"
#include "Time.h"

int Scene::nextID = 0;
std::vector<GameObject*> Scene::_listOfGameObjects;
std::vector<GameObject*> Scene::_listOfDrawableGameObjects;

Scene::Scene(std::string name)
{
	_id = ++nextID;
	_name = name;

	InitScene();
	//_pTilemap->SetSpriteSheet(_pSpritesheet);

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
	delete(_pDay);
}

void Scene::SceneStart()
{
	for (GameObject* obj : _listOfGameObjects) {
		obj->Start();
	}
}

void Scene::InitScene()
{
	//_listOfGameObjects.clear();

	/////////////
	//TEST CODE//
	/////////////

	Heap* gameObjectHeap = HeapManager::CreateHeap("GameObject", "Root");

	_pDay = new Day();

	//ResourceManager::InstantiateTexture("fish", new Texture2D("Fish.png"));
	//ResourceManager::InstantiateTexture("character", new Texture2D("Resources/Images/Spritesheets/AlexTest.png", true));

	//AddGameObject(_pTestObject2);
	//AddGameObject(_pButtonTestingObject);
	//AddGameObject(_pPlayer);

	//GameObject* _pTextObj = new GameObject("TEXTOBJ", ObjectType::UI);
	//_pTextObj->AddComponent(new TextComponent(_pTextObj));
	//_pTextObj->SetType(ObjectType::UI);
	//AddGameObject(_pTextObj);
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
		TextComponent* tc = obj->GetComponent<TextComponent>();
		if (tc != nullptr) {
			tc->OnStart();
			tc->OnUpdate();
		}
	}
}

void Scene::Update()
{
	if (_timeProgression)
	{
		_pDay->Update();
	}
	UpdateObjects();
	UpdateUI();

	/////////////
	//TEST CODE//     BOX COLISSIONS
	/////////////
	//if (_listOfGameObjects[0]->GetComponent<BoxColliderComponent>()->Intersects(_listOfGameObjects[1]->GetComponent<BoxColliderComponent>()->GetCollisionRect()))
	//{
	//	std::cout << "Boxes are colliding" << std::endl;
	//}
	//glm::vec2 pos = _listOfGameObjects[1]->GetTransform()->GetPosition();
	//if (Input::IsKeyDown(KEY_T))
	//{
	//	_listOfGameObjects[1]->GetTransform()->SetPosition(pos.x + 0.5, pos.y );
	//}
	//if (Input::IsKeyDown(KEY_G))
	//{
	//	_listOfGameObjects[1]->GetTransform()->SetPosition(pos.x - 0.5, pos.y );
	//}
	//Physics::Intersects(_pCircleTest->GetComponent<CircleCollider>(), _pTestObject2->GetComponent<BoxColliderComponent>());
	//Physics::Intersects(_pTriggerBox->GetComponent<BoxColliderComponent>(), _pPlayer->GetComponent<BoxColliderComponent>());
	//////////////////
	//END OF TEST CODE
	//////////////////
}

void Scene::UpdateUI()
{

}

void Scene::UpdateObjects()
{
	//Cycles through all gameobjects in the scene and updates them
	for (GameObject* obj : _listOfGameObjects)
	{
		obj->Update();
	}

	for (GameObject* obj : _gameObjectsToRemove) {
		_listOfGameObjects.erase(std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), obj));
		

		delete obj;
	}
	_gameObjectsToRemove.clear();
}

void Scene::RenderScene(Camera* cam)
{
	Renderer2D::BeginRender(cam);

	_pTilemap->RenderMap(cam);

	for (auto& obj : _listOfDrawableGameObjects) {
		//TODO: Text won't render here as it uses its own internal texture data.
		Texture2D* objTex = obj->GetComponent<Texture2D>();

		if (objTex != nullptr) {
			if (obj->GetTag() == "UI") {
				Renderer2D::DrawUIQuad(obj->GetTransform()->GetRenderQuad(), obj->GetComponent<Texture2D>());
			}
			else if (obj->GetTag() == "PLAYER") {
				SpriteComponent* sc = obj->GetComponent<SpriteComponent>();
				Renderer2D::DrawQuad(obj->GetTransform()->GetRenderQuad(), objTex, sc->GetSprite()->GetTexCoords());
				//Renderer2D::DrawQuad(obj->GetTransform()->GetRenderQuad(), objTex);
			}
			else {
				Renderer2D::DrawQuad(obj->GetTransform()->GetRenderQuad(), objTex);
			}
		}
	}

	//Renderer2D::DrawQuad(_pPlayer->GetTransform()->GetRenderQuad(), ResourceManager::GetTexture("character"),
	//	_pPlayer->GetComponent<SpriteComponent>()->GetSprite()->GetTexCoords());

	Renderer2D::EndRender();
}

void Scene::CircleBoxTest()
{
	std::cout << "Circle Box Collision" << std::endl;
}

void Scene::SceneBox()
{
	std::cout << "Collide with scene transfer" << std::endl;
}

GameObject* Scene::AddGameObject(GameObject* gameObject)
{
	_listOfGameObjects.push_back(gameObject);
	Physics::SetupScenePhysics();
	return gameObject;
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	_gameObjectsToRemove.emplace_back(gameObject);
	//Searches for the desired object and deletes it if it is found
	//_listOfGameObjects.erase(std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), gameObject));
	//delete gameObject;
	//gameObject = nullptr;
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
//
//void Scene::LoadScene(const std::string& filename)
//{
//	if (_pTilemap != nullptr) {
//		_pTilemap->LoadTileMap();
//	}
//
//	//Clears the list (this is in case we are going from one scene to the next)
//	_listOfGameObjects.clear();
//
//	//Creates a stream
//	StreamFile stream;
//	//Opens the stream for reading
//	stream.OpenRead(filename);
//
//	//recreates the list of gameobjects
//	_listOfGameObjects = std::vector<GameObject*>();
//
//	//Read in the amount of game objects in the scene
//	int amountOfGo = ReadInt(stream);
//	_listOfGameObjects.resize(amountOfGo);
//
//	//Read in the information for each game object
//	for (int i = 0; i < amountOfGo; ++i) {
//		GameObject* go = new GameObject();
//		go->LoadState(stream);
//		_listOfGameObjects[i] = go;
//	}
//
//	//FindObjectOfType<PlayerMovement>()->SetTileMap(_pTilemap);
//
//	stream.Close();
//}

//void Scene::SaveScene(const std::string& filename)
//{
//	if (_pTilemap != nullptr) {
//		_pTilemap->SaveTilemap();
//	}
//
//	//Creates a stream file object
//	StreamFile stream;
//	//Opens this stream for writing
//	stream.OpenWrite(filename);
//
//	//Writes the amount of game objects in the scene
//	WriteInt(stream, _listOfGameObjects.size());
//
//	//Cycles through each object and calls there save method
//	for (int i = 0; i < _listOfGameObjects.size(); ++i) {
//		_listOfGameObjects[i]->SaveState(stream);
//	}
//
//	//Closes the stream
//	stream.Close();
//}
//
//void Scene::Save()
//{
//	SaveScene("Resources/Scenes/" + _name);
//}

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



//Find first GameObject with the desired tag 
GameObject* Scene::FindObjectWithTag(const std::string& tagName)
{
	for (GameObject* obj : _listOfGameObjects) {
		if (obj->GetTag() == tagName) {
			return obj;
		}
	}
	return nullptr;
}

std::vector<GameObject*> Scene::FindGameObjectsWithTag(const std::string& tagName)
{
	std::vector<GameObject*> objects;
	for (GameObject* obj : _listOfGameObjects) {
		if (obj->GetTag() == tagName) {
			objects.emplace_back(obj);
		}
	}
	return objects;
}
