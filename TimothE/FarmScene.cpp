#include "FarmScene.h"
#include "Button.h"
#include "SpriteComponent.h"
#include "CameraManager.h"
#include "Player.h"

FarmScene::~FarmScene()
{
	
}

void FarmScene::UpdateUI()
{

}

void FarmScene::UpdateObjects()
{
	Scene::UpdateObjects();

	//glm::vec2 forward = _pPlayerObject->GetTransform()->GetForward();
	//glm::vec2 pos = forward * 0.1f;
	//pos.y += 0.1f;
	//
	////TIM_LOG_LOG("Player forward: " << forward.x << ", " << forward.y);
	////TIM_LOG_LOG("Weapon Pos: " << pos.x << ", " << pos.y);
	//_pWeaponObject->GetTransform()->SetPosition(pos);

	if (_pDay->NightStart())
	{
		_pWaveController->StartWaves(_pDay->GetDayCount());

		for (GameObject* go : _pWaveController->GetEnemies())
		{
			AddGameObject(go);
		}
	}
	else if (!_pDay->IsDay())
	{
		if (_pWaveController->TryNewWave())
		{
			for (GameObject* enemy : _pWaveController->GetEnemies())
			{
				AddGameObject(enemy);
			}
		}
	}

	if (Input::IsKeyDown(KEY_G)) {
		_pTilemap->AddTileAt(2, 15, 12, CameraManager::CurrentCamera());
	}
}

void FarmScene::InitScene()
{
	_listOfGameObjects.clear();
	_listOfDrawableGameObjects.clear();

	_pSpritesheet = ResourceManager::GetSpriteSheet("testSheet");

	_pStartButton = new GameObject("BUTTON");
	_pStartButton->AddComponent(new Button(_pStartButton));
	_pStartButton->AddComponent(new BoxColliderComponent(_pStartButton));
	//pStartButton->AddComponent(new TextComponent(_pTestObject));


	//_pStartButton->LoadTexture(ResourceManager::GetTexture("Button"));
	_pStartButton->SetShader("ui");
	_pStartButton->GetTransform()->SetPosition(0.0f, 0.0f);
	_pStartButton->GetTransform()->SetScale({ 0.2f, 0.2f });
	//_pStartButton->SetType(ObjectType::UI);
	//AddGameObject(_pStartButton);

	//_pPlayerObject->AddComponent(new Fighter(_pPlayerObject));
	//_pPlayerMovement = new PlayerInputComponent(_pPlayerObject);

	_pWeaponObject = new GameObject("Weapon");
	//_pWeaponObject->SetParent(_pPlayerObject);
	_pWeaponObject->AddComponent<Texture2D>(ResourceManager::GetTexture("swords"));
	_pWeaponObject->GetTransform()->SetScale({0.20f, 0.20f});
	_pWeaponObject->GetTransform()->SetPosition({1.5f, 0.0f});
	SpriteComponent* pWeaponSC = _pWeaponObject->AddComponent<SpriteComponent>(new SpriteComponent(_pWeaponObject));

	AnimatedSpritesheet* pWeaSS = new AnimatedSpritesheet(ResourceManager::GetTexture("swords"), 16, 16, false);
	pWeaponSC->SetSprite(pWeaSS->GetSpriteAtIndex(6));

	AddGameObject(_pWeaponObject);

	_pPlayer = new Player();
	AddGameObject(_pPlayer);

	//_pPlayerObject->AddComponent(_pPlayerMovement);
	//_pPlayerObject->AddComponent(ResourceManager::GetTexture("character"));
	//AddGameObject(_pPlayerObject);

	_pTilemap = new TileMap(_name);

	//_pSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(0));
	//_pTilemap->SetSpriteSheet(ResourceManager::GetSpriteSheet("testSheet"));
	//_pTilemap->LoadTileMap();

	_pWaveController = new WaveController(this);
}
