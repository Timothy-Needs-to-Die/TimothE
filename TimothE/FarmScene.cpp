#include "FarmScene.h"
#include "Button.h"
#include "SpriteComponent.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "Player.h"
#include "ResourceNodeObject.h"
#include "Wave.h"
#include "OffensiveStructureObject.h"
#include "AIMovementCompnent.h"
#include "StructureObject.h"

FarmScene::~FarmScene()
{
	
}

void FarmScene::UpdateUI()
{

}

void FarmScene::UpdateObjects()
{
	Scene::UpdateObjects();

	if (Input::IsKeyDown(KEY_5)) {
		SceneManager::SetCurrentScene(SceneManager::CreateScene(ResourceManager::GetScene("TownScene")));
	}


	//glm::vec2 forward = _pPlayerObject->GetTransform()->GetForward();
	//glm::vec2 pos = forward * 0.1f;
	//pos.y += 0.1f;
	//
	////TIM_LOG_LOG("Player forward: " << forward.x << ", " << forward.y);
	////TIM_LOG_LOG("Weapon Pos: " << pos.x << ", " << pos.y);
	//_pWeaponObject->GetTransform()->SetPosition(pos);

	//if (_pDay->NightStart())
	//{
	//	_pWaveController->StartWaves(_pDay->GetDayCount());
	//
	//	for (GameObject* go : _pWaveController->GetEnemies())
	//	{
	//		AddGameObject(go);
	//	}
	//}
	//else if (!_pDay->IsDay())
	//{
	//	if (_pWaveController->TryNewWave())
	//	{
	//		for (GameObject* enemy : _pWaveController->GetEnemies())
	//		{
	//			AddGameObject(enemy);
	//		}
	//	}
	//}

	if (Input::IsKeyDown(KEY_G)) {
		//_pTilemap->AddTileAt(2, 15, 12, CameraManager::CurrentCamera());
	}

	if (currentRow != _pAnimSheet->GetCurrentRow()) {
		_pAnimSheet->SetCurrentRow(currentRow);
	}

	_pAnimSheet->SetStationary(!_pMovement->IsMoving());
	_pSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(_pAnimSheet->GetCurrentIndex()));


}

void FarmScene::InitScene()
{
	Scene::InitScene();

	_pSpritesheet = ResourceManager::GetSpriteSheet("testSheet");

	_pStartButton = new GameObject("BUTTON", ObjectType::UI);
	_pStartButton->AddComponent(new Button(_pStartButton));
	_pStartButton->AddComponent(new BoxColliderComponent(_pStartButton));
	//pStartButton->AddComponent(new TextComponent(_pTestObject));


	//_pStartButton->LoadTexture(ResourceManager::GetTexture("Button"));
	_pStartButton->SetShader("ui");
	_pStartButton->GetTransform()->SetPosition(0.0f, 0.0f);
	_pStartButton->GetTransform()->SetScale({ 0.2f, 0.2f });
	_pStartButton->SetType(ObjectType::UI);
	//AddGameObject(_pStartButton);

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

	farmland = new FarmlandManager("Farmland Manager");
	AddGameObject(farmland);

	//OffensiveStructureObject* _pTower = new OffensiveStructureObject("Test Tower");
	//AddGameObject(_pTower);

	_pSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(0));
	//_pTilemap->SetSpriteSheet(ResourceManager::GetSpriteSheet("testSheet"));
	//_pTilemap->LoadTileMap();

	LightSource ls = LightSource();
	ls.worldPos = glm::vec2(0.0f, 0.0f);

	_pLightManager = new LightLevelManager();
	_pLightManager->AddLightSource(ls);

	_pLightManager->UpdateLightMap(_pTilemap);
}

void FarmScene::AddStructure(StructureObject* object)
{
	AddGameObject(object);
	_pStructures.emplace_back(object);
}
