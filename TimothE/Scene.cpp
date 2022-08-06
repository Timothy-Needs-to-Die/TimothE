#include "pch.h"

#include "Texture2D.h"
#include "Scene.h"
#include "TextComponent.h"
#include "StreamFile.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Core/Graphics/Renderer2D.h"

#include "Core/Graphics/SubTexture2D.h"
#include "PlayerInputComponent.h"
#include "SpriteComponent.h"
#include "Time.h"

#include "Player.h"
#include "AStar.h"
#include "SceneTransitionObject.h"
#include "CameraManager.h"

#include "Core/Graphics/Framebuffer.h"

std::vector<GameObject*> Scene::_listOfGameObjects;
std::vector<GameObject*> Scene::_listOfDrawableGameObjects;
std::vector<GameObject*> Scene::_listofDrawableUIObjects;

Scene::Scene(std::string name)
{
	_name = name;
	_pFb = new Framebuffer(ResourceManager::GetShader("framebuffer"));
}

Scene::~Scene()
{
	for (GameObject* obj : _listOfGameObjects)
	{
		delete obj;
	}
}

void Scene::SceneStart(glm::vec2 spawnPoint)
{
	if (_pPlayer != nullptr && spawnPoint != glm::vec2{ 0.0f,0.0f }) {
		_pPlayer->GetTransform()->SetPosition(spawnPoint);
	}
	for (GameObject* obj : _listOfGameObjects) {
		if (obj == nullptr) continue;
		obj->Start();
		obj->Update();
	}
}

void Scene::InitScene(bool hasPlayer)
{
	_listOfGameObjects.clear();
	_gameObjectsToRemove.clear();

	//Disables the level from being rendered until the scene is loaded
	_readyToShow = false;

	//Turns on the black screen at max intensity
	_pFb->GetAttachedShader()->SetBool("shouldBeBlack", true);
	_pFb->GetAttachedShader()->SetFloat("blackAlpha", 1.0f);

	//Renders the black frame
	RenderScene(CameraManager::MainCamera());
	glfwSwapBuffers(Window::GetGLFWWindow());

	if (_pAstarObject == nullptr) {
		_pAstarObject = new AStar();
	}

	if (_hasTilemap) {
		if (_pLightManager != nullptr) {
			_pLightManager->UpdateLightMap();
		}

		CameraManager::MainCamera()->SetTileMap(_pTilemap);


		//Finds all of the destination points on the tilemap to create the transition objects
		std::unordered_map<std::string, glm::vec2> destinationPoints = _pTilemap->GetMapDestinationPoints();
		for (auto& element : destinationPoints) {
			//element.first is the name of the destination
			SceneTransitionObject* pSceneTransition = new SceneTransitionObject(element.first);

			//element.second is the position
			pSceneTransition->GetTransform()->SetPosition(element.second);
			pSceneTransition->GetTransform()->SetScale({ 0.2f, 0.2f });
			AddGameObject(pSceneTransition);
		}
	}

	if (hasPlayer) {
		if (_pPlayer == nullptr) {
			_pPlayer = new Player();
		}
		AddGameObject(_pPlayer);

		CameraManager::MainCamera()->SetFollowTarget(_pPlayer);
		if (_hasTilemap) {
			_pPlayer->GetTransform()->SetPosition(_pTilemap->GetPlayerSpawn());
		}
	}

	_pFb->GetAttachedShader()->SetBool("shouldBeBlack", false);
	_pFb->GetAttachedShader()->SetBool("fadingIn", true);
	_readyToShow = true;
	_fadingIn = true;
	_fade = 1.0f;

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

void Scene::LoadTileMap()
{
	if (!_hasTilemap) return;

	_pTilemap = new TileMap(_name);
	_pTilemap->LoadTileMap("Resources/Tilemaps/" + _name + ".tmx");

	_pAstarObject = new AStar();

	_pAstarObject->SetMap(_pTilemap);
	_pLightManager = new LightLevelManager(_pTilemap);
	_pLightManager->SetWorldLightLevel(2);
	_pLightManager->SetMinLightLevel(1);
	_pLightManager->SetMaxLightLevel(8);
	_pLightManager->UpdateLightMap();

	_spawnPoints = _pTilemap->GetMapSpawnPoints();
}

void Scene::EditorUpdate()
{
	//Cycles through all gameobjects in the scene and calculates there transform.
	//Needed for the editor window to work smoothly
	for (GameObject* obj : _listOfGameObjects) {
		if (!obj->IsActive()) continue;
		if (obj->IsToBeDestroyed()) continue;

		TextComponent* tc = obj->GetComponent<TextComponent>();
		if (tc != nullptr) {
			tc->OnStart();
			tc->OnUpdate();
		}
	}
}

void Scene::MovePlayerToSpawnPoint(std::string spawnPointName)
{
	_pPlayer->GetTransform()->SetPosition(_spawnPoints[spawnPointName]);
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
	if (!_readyToShow) return;

	//Cycles through all gameobjects in the scene and updates them

	for (GameObject* obj : _listOfGameObjects)
	{
		if (obj == nullptr) continue;

		if (obj->IsToBeDestroyed()) continue;

		if (!obj->IsActive()) continue;

		obj->Update();
		//TIM_LOG_LOG(obj->IsToBeDestroyed());
	}

	Physics::UpdateWorld();
}

void Scene::FrameEnd()
{

	for (GameObject* obj : _gameObjectsToRemove) {
		Physics::RemoveCollider(obj->GetComponent<ColliderBase>());

		std::vector<GameObject*>::iterator it = std::find(_listOfDrawableGameObjects.begin(), _listOfDrawableGameObjects.end(), obj);
		if (it != _listOfDrawableGameObjects.end()) {
			_listOfDrawableGameObjects.erase(it);
		}

		std::vector<GameObject*>::iterator it2 = std::find(_listOfGameObjects.begin(), _listOfGameObjects.end(), obj);
		if (it2 != _listOfGameObjects.end()) {
			_listOfGameObjects.erase(it2);
		}

		std::vector<GameObject*>::iterator it3 = std::find(_listofDrawableUIObjects.begin(), _listofDrawableUIObjects.end(), obj);
		if (it3 != _listofDrawableUIObjects.end()) {
			_listofDrawableUIObjects.erase(it3);
		}
	}


	_gameObjectsToRemove.clear();
	Physics::EndFrame();
}

void Scene::RenderScene(std::shared_ptr<Camera> cam)
{
	if (!_readyToShow) {
		_pFb->BindFramebuffer();
		_pFb->UnbindFramebuffer();
		_pFb->DrawFramebuffer();
		return;
	}

	if (_fadingIn) {
		_fade -= _fadeDecrement;
		_pFb->GetAttachedShader()->SetFloat("blackAlpha", _fade);

		if (_fade <= 0.0f) {
			_pFb->GetAttachedShader()->SetFloat("blackAlpha", 0.0f);
			_pFb->GetAttachedShader()->SetBool("fadingIn", false);
			_fadingIn = false;
			_fade = 1.0f;
		}
	}

	_pFb->BindFramebuffer();

	if (_hasTilemap) {
		_pTilemap->RenderMap(cam);
	}

	Renderer2D::BeginRender(cam);

	if (_listOfDrawableGameObjects.size() == 0) return;
	for (std::vector<GameObject*>::iterator it = _listOfDrawableGameObjects.begin(); it != _listOfDrawableGameObjects.end(); ++it) {
		GameObject* obj = *it;
		if (!obj->IsActive() || obj->IsToBeDestroyed()) continue;

		SpriteComponent* sc = obj->GetComponent<SpriteComponent>();
		if (sc) {
			if (!sc->IsEnabled()) continue;

			if (_hasTilemap) {
				int light = _pTilemap->GetLightLevelAtPosition(obj->GetTransform()->GetPosition());
				Renderer2D::DrawQuad(obj->GetTransform()->GetRenderQuad(), sc->GetSprite()->GetTexture(), sc->GetSprite()->GetTexCoords(), light);
			}
			else
			{
				Renderer2D::DrawQuad(obj->GetTransform()->GetRenderQuad(), sc->GetSprite()->GetTexture(), sc->GetSprite()->GetTexCoords());
			}
		}
	}

	Renderer2D::EndRender();

	Renderer2D::BeginRender(cam);

	for (std::vector<GameObject*>::iterator it = _listofDrawableUIObjects.begin(); it != _listofDrawableUIObjects.end(); ++it) {
		GameObject* obj = *it;

		if (!obj->IsActive() || obj->IsToBeDestroyed()) continue;

		SpriteComponent* sc = obj->GetComponent<SpriteComponent>();
		if (sc) {
			if (!sc->IsEnabled()) continue;
			Renderer2D::DrawUIQuad(obj->GetTransform()->GetRenderQuad(), sc->GetSprite()->GetTexture(), sc->GetSprite()->GetTexCoords());
			continue;
		}

		TextComponent* tc = obj->GetComponent<TextComponent>();
		if (tc) {
			tc->Render();
		}
	}

	Renderer2D::EndRender();

	_pFb->UnbindFramebuffer();

	_pFb->DrawFramebuffer();
}

void Scene::Unload(bool deleteTileMap /*= false*/)
{
	for (auto& obj : _listOfGameObjects) {
		if (obj->GetTag() == "PLAYER" || obj->IsChildOf(_pPlayer)) continue;

		_gameObjectsToRemove.emplace_back(obj);
	}

	if (deleteTileMap && _hasTilemap && _pTilemap) {
		delete _pTilemap;
		_pTilemap = nullptr;
	}

	FrameEnd();
}

GameObject* Scene::AddGameObject(GameObject* gameObject)
{
	_listOfGameObjects.push_back(gameObject);

	return gameObject;
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	if (gameObject == nullptr) return;

	std::vector<GameObject*>::const_iterator it = std::find(_gameObjectsToRemove.begin(), _gameObjectsToRemove.end(), gameObject);

	gameObject->SetToBeDestroyed(true);

	if (it == _gameObjectsToRemove.end()) {
		for (auto& child : gameObject->GetChildren()) {
			RemoveGameObject(child);
		}

		_gameObjectsToRemove.emplace_back(gameObject);
	}
}

bool SortbyAscendingDrawOrder(GameObject* a, GameObject* b)
{
	SpriteComponent* as = a->GetComponent<SpriteComponent>();
	SpriteComponent* bs = b->GetComponent<SpriteComponent>();
	return (as->GetDrawOrder() < bs->GetDrawOrder());
}

void Scene::AddedComponentHandler(GameObject* gameObject, Component* comp)
{
	//If this component is a graphics component
	if (comp->GetType() == Component::Types::SpriteType) {
		//If the Gameobject is not already in the drawables list
		if (std::find(_listOfDrawableGameObjects.begin(), _listOfDrawableGameObjects.end(), gameObject) == _listOfDrawableGameObjects.end()) {
			_listOfDrawableGameObjects.emplace_back(gameObject);
			std::sort(_listOfDrawableGameObjects.begin(), _listOfDrawableGameObjects.end(), SortbyAscendingDrawOrder);
		}
	}

	if (gameObject->GetTag() == "UI") {
		if (std::find(_listofDrawableUIObjects.begin(), _listofDrawableUIObjects.end(), gameObject) == _listofDrawableUIObjects.end()) {
			_listofDrawableUIObjects.emplace_back(gameObject);
		}
	}
}

void Scene::RemoveComponentHandler(GameObject* gameObject, Component* comp)
{
	if (comp->GetType() != Component::SpriteType) return;

	//remove from drawables if the component is a sprite type
	_listOfDrawableGameObjects.erase(std::find(_listOfDrawableGameObjects.begin(), _listOfDrawableGameObjects.end(), gameObject));
}

GameObject* Scene::GetGameObjectByName(std::string name)
{
	//Cycles through all gameobjects in the scene
	for (GameObject* obj : _listOfGameObjects) {
		if (!obj->IsActive()) continue;
		if (obj->IsToBeDestroyed()) continue;

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
		if (!obj->IsActive()) continue;

		if (obj->IsToBeDestroyed()) continue;
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
		if (!obj->IsActive()) continue;

		if (obj->IsToBeDestroyed()) continue;
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
		if (obj == nullptr || obj->IsToBeDestroyed()) continue;

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
		if (!obj->IsActive() || obj->IsToBeDestroyed()) continue;

		if (obj->GetTag() == tagName) {
			objects.emplace_back(obj);
		}
	}
	return objects;
}

void Scene::PopulateToolVector()
{
	std::vector<std::vector<std::string>> loadedData = CSVReader::RequestDataFromFile("Resources/Data/BlacksmithVendorConfig.csv");
	for (int i = 0; i < loadedData.size(); i++) {
		ToolConfig newConfig;
		newConfig.price = std::stoi(loadedData[i][3]);
		newConfig.name = loadedData[i][1];
		newConfig.resourceCost.woodRequired = std::stoi(loadedData[i][4]);
		newConfig.resourceCost.stoneRequired = std::stoi(loadedData[i][5]);
		newConfig.resourceCost.metalRequired = std::stoi(loadedData[i][6]);
		newConfig.resourceCost.coalRequired = std::stoi(loadedData[i][7]);
		newConfig.type = (ToolType)std::stoi(loadedData[i][10]);
		newConfig.damagePerHit = std::stoi(loadedData[i][8]);
		newConfig.townLevelRequired = std::stoi(loadedData[i][0]);
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
		newConfig.growthPerDay = std::stoi(loadedData[i][4]);
		newConfig.type = (SeedType)std::stoi(loadedData[i][5]);
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
	}
}