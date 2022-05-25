#include "FarmScene.h"
#include "Button.h"
#include "SpriteComponent.h"
#include "CameraManager.h"
#include "Player.h"
#include "ResourceNodeObject.h"
#include "WaveManager.h"
#include "OffensiveStructureObject.h"
#include "AIMovementCompnent.h"
#include "StructureObject.h"
#include "GameTimeManager.h"
#include "Bed.h"
#include "PlayerHealth.h"
#include "AIController.h"
#include "Enemy.h"

FarmScene::~FarmScene()
{

}

void FarmScene::UpdateUI()
{

}

void FarmScene::UpdateObjects()
{
	Scene::UpdateObjects();

	_pGameTime->Update();

	if (Input::IsKeyDown(KEY_5)) {
		SceneManager::SetCurrentScene(SceneManager::CreateScene(ResourceManager::GetScene("TownScene")));
	}

	if (Input::IsKeyDown(KEY_G)) {
		//_pTilemap->AddTileAt(2, 15, 12, CameraManager::CurrentCamera());
	}
	/*if (Input::IsKeyDown(KEY_H))
	{
		if (_pPlayer != nullptr)
		{
			PlayerHealth* h = _pPlayer->GetComponent<PlayerHealth>();
			if (h != nullptr)
			{
				h->TakeDamage(50);
			}
		}
	}*/

	if (!_pGameTime->IsDay()) {
		if (Input::IsKeyDown(KEY_P)) {
			_pGameTime->EndNight();
			_pGameTime->StartNewDay();
		}
	}

	if (Input::IsKeyUp(KEY_I)) {
		_inventoryKeyPressed = false;
	}

	if (Input::IsKeyDown(KEY_I)) {
		if (_inventoryKeyPressed) return;

		_inventoryKeyPressed = true;

		bool current = _pInventoryScreen->GetAllActive();

		//_pInventoryScreen->SetAllActive(!current);
		//_pInventoryScreen->OnUpdate();
		//if (_pInventoryScreen == nullptr)
		//{
			//_pInventoryScreen->GetTransform()->SetPosition(50.0f, 50.0f);
			//_pInventoryScreen->GetTransform()->SetScale({ 0.25f, 0.25f });
		//}
	}


	Physics::UpdateWorld();
}

void FarmScene::InitScene()
{
	Scene::InitScene();

	_pInventoryScreen = new InventoryScreen();
	AddGameObject(_pInventoryScreen);
	_pInventoryScreen->SetAllActive(false);

	_pSpritesheet = ResourceManager::GetSpriteSheet("testSheet");

	_pGameTime = new GameTimeManager();

	//_pStartButton = new GameObject("BUTTON", "UI");
	//_pStartButton->AddComponent(new Button(_pStartButton));
	//_pStartButton->AddComponent(new BoxColliderComponent(_pStartButton));
	//_pStartButton->AddComponent(new TextComponent(_pTestObject));
	//_pStartButton->AddComponent(ResourceManager::GetTexture("Button"));
	//AddGameObject(_pStartButton);

	//_pStartButton->GetTransform()->SetPosition(0.0f, 0.0f);
	//_pStartButton->GetTransform()->SetScale({ 0.2f, 0.2f });
	//GameObject* pPathFinder = new GameObject("Pathfinder");
	//pPathFinder->AddComponent<AStar>(new AStar(pPathFinder));
	//AddGameObject(pPathFinder);

	_pWeaponObject = new GameObject("Weapon");
	_pWeaponObject->AddComponent<Texture2D>(ResourceManager::GetTexture("swords"));
	_pWeaponObject->GetTransform()->SetScale({0.20f, 0.20f});
	_pWeaponObject->GetTransform()->SetPosition({1.5f, 0.0f});
	SpriteComponent* pWeaponSC = _pWeaponObject->AddComponent<SpriteComponent>(new SpriteComponent(_pWeaponObject));

	AnimatedSpritesheet* pWeaSS = new AnimatedSpritesheet(ResourceManager::GetTexture("swords"), 16, 16, "weaponAnim", false);
	pWeaponSC->SetSprite(pWeaSS->GetSpriteAtIndex(6));

	AddGameObject(_pWeaponObject);

	_pPlayer = new Player();
	AddGameObject(_pPlayer);

	//_pAStar = new GameObject("Pather");
	//AStar* path = _pAStar->AddComponent(new AStar(_pAStar));
	//path->SetMap(SceneManager::GetCurrentScene()->GetTileMap());

	//_pWaveController = new WaveController(this);

	//_pDay = new Day();
	//_pDay->SetWaveController(_pWaveController);

	_pWoodNode = new ResourceNodeObject(Wood);
	_pWoodNode->GetTransform()->SetPosition(5.0f, 1.0f);
	AddGameObject(_pWoodNode);

	_pMetalNode = new ResourceNodeObject(Metal);
	_pMetalNode->GetTransform()->SetPosition(6.0, 1.0f);
	AddGameObject(_pMetalNode);

	_pStoneNode = new ResourceNodeObject(Stone);
	_pStoneNode->GetTransform()->SetPosition(7.0, 1.0f);
	AddGameObject(_pStoneNode);


	_pCoalNode = new ResourceNodeObject(Coal);
	_pCoalNode->GetTransform()->SetPosition(8.0, 1.0f);
	AddGameObject(_pCoalNode);

	//LIGHTING TEST CODE//
	_pLightManager = new LightLevelManager(_pTilemap);
	_pLightManager->SetWorldLightLevel(5);
	_pLightManager->SetMinLightLevel(1);
	_pLightManager->SetMaxLightLevel(8);

	//Add Light Sources
	LightSource campfire = LightSource();
	campfire.worldPos = glm::vec2(16.75f, 3.0f);
	_pLightManager->AddLightSource(campfire);

	//Update Light Map
	_pLightManager->UpdateLightMap();
	//LIGHTING END//
}

void FarmScene::AddStructure(StructureObject* object)
{
	AddGameObject(object);
	_pStructures.emplace_back(object);
	_pAstarObject->UpdateNodeObstacleStatus(_pTilemap->GetTileAtWorldPos(0, object->GetTransform()->GetPosition())->pos, true);
}

void FarmScene::RemoveStructure(StructureObject* object)
{
	for (int i = 0; i < _pStructures.size(); ++i) {
		StructureObject* pObject = _pStructures[i];

		if (pObject != object) continue;

		_pTilemap->SetCollidableAtLayer(5, pObject->GetTransform()->GetPosition(), false);

		_pAstarObject->UpdateNodeObstacleStatus(_pTilemap->GetTileAtWorldPos(0, pObject->GetTransform()->GetPosition())->pos, false);
	}

	std::vector<StructureObject*>::iterator it = std::find(_pStructures.begin(), _pStructures.end(), object);
	if (it != _pStructures.end()) {
		_pStructures.erase(it);
		RemoveGameObject(object);
	}
}

std::vector<class StructureObject*> FarmScene::GetStructures() const
{
	return _pStructures;
}

void FarmScene::GameOver()
{
	// todo: add proper gameover
	TIM_LOG_LOG("Game over");
}
