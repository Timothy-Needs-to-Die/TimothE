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

std::vector<GameObject*> Scene::_listOfGameObjects;
std::vector<GameObject*> Scene::_listOfDrawableGameObjects;

Scene::Scene(std::string name)
{
	_name = name;
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

void Scene::InitScene()
{
	_listOfGameObjects.clear();
	_listOfDrawableGameObjects.clear();
	_gameObjectsToRemove.clear();


	_pTilemap = new TileMap(_name);
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
	UpdateObjects();
	UpdateUI();
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

	Physics::UpdateWorld();
}

void Scene::FrameEnd()
{
	for (GameObject* obj : _gameObjectsToRemove) {
		_listOfGameObjects.erase(std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), obj));

		std::vector<GameObject*>::iterator it = std::find(_listOfDrawableGameObjects.begin(), _listOfDrawableGameObjects.end(), obj);
		if (it != _listOfDrawableGameObjects.end()) {
			_listOfDrawableGameObjects.erase(it);
		}

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
		SpriteComponent* sc = obj->GetComponent<SpriteComponent>();

		if (objTex != nullptr || sc != nullptr) {
			if (obj->GetTag() == "UI") {
				Renderer2D::DrawUIQuad(obj->GetTransform()->GetRenderQuad(), obj->GetComponent<Texture2D>());
			}
			else {
				if (sc) {
					Renderer2D::DrawQuad(obj->GetTransform()->GetRenderQuad(), sc->GetSprite()->GetTexture(), sc->GetSprite()->GetTexCoords());
				}
				else {
					Renderer2D::DrawQuad(obj->GetTransform()->GetRenderQuad(), objTex);
				}
			}
		}
	}

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
	return gameObject;
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	_gameObjectsToRemove.emplace_back(gameObject);
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

void Scene::PopulateToolVector()
{
	std::vector<std::vector<std::string>> loadedData = CSVReader::RequestDataFromFile("Resources/Data/ItemsConfig.csv");
		for (int i = 0; i < loadedData.size(); i++) {
			ToolConfig newConfig;
			newConfig.price = std::stoi(loadedData[i][2]);
			newConfig.name = loadedData[i][0];
			newConfig.resourceCost.woodRequired = std::stoi(loadedData[i][3]);
			newConfig.resourceCost.stoneRequired = std::stoi(loadedData[i][4]);
			newConfig.resourceCost.metalRequired = std::stoi(loadedData[i][5]);
			newConfig.resourceCost.coalRequired = std::stoi(loadedData[i][6]);
			newConfig.type = (ToolType)std::stoi(loadedData[i][11]);
			newConfig.damagePerHit = std::stoi (loadedData[i][7]);
			newConfig.townLevelRequired = std::stoi(loadedData[i][10]);

		}
}

void Scene::PopulateSeedVector()
{
	std::vector<std::vector<std::string>> loadedData = CSVReader::RequestDataFromFile("Resources/Data/SeedConfigs");

	for (int i = 0; i < loadedData.size(); i++) {
		SeedConfig newConfig;
		newConfig.name = loadedData[i][1];
		newConfig.price = std::stoi(loadedData[i][2]);
		newConfig.description = loadedData[i][3];
		newConfig.growthRate = std::stoi(loadedData[i][4]);
		newConfig.type = (CropType)std::stoi(loadedData[i][5]);
	}
}

void Scene::PopulateCropVector()
{
	std::vector<std::vector<std::string>> loadedData = CSVReader::RequestDataFromFile("Resources/Data/CropsConfig.csv");

	for (int i = 0; i < loadedData.size(); i++) {
		CropConfig newConfig;
		newConfig.name = loadedData[i][1];
		newConfig.sellPrice = std::stoi(loadedData[i][2]);
		newConfig.description = loadedData[i][3];
		newConfig.type = (CropType)std::stoi(loadedData[i][5]);
	}
}
