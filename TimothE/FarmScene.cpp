#include "FarmScene.h"
#include "Button.h"
#include "SpriteComponent.h"
#include "CameraManager.h"
#include "Player.h"

FarmScene::~FarmScene()
{
	if (_pStartButton) delete(_pStartButton);
	if (_pWeaponObject) delete(_pWeaponObject);
	if (_pSpritesheet) delete(_pSpritesheet);
	if (_pPlayer) delete(_pPlayer);
	if (_pDay) delete(_pDay);
	if (_pWaveController) delete(_pWaveController);
}

void FarmScene::UpdateUI()
{

}

void FarmScene::UpdateObjects()
{
	if (_timeProgression)
	{
		_pDay->Update();
	}

	Scene::UpdateObjects();

	//glm::vec2 forward = _pPlayerObject->GetTransform()->GetForward();
	//glm::vec2 pos = forward * 0.1f;
	//pos.y += 0.1f;
	//
	////TIM_LOG_LOG("Player forward: " << forward.x << ", " << forward.y);
	////TIM_LOG_LOG("Weapon Pos: " << pos.x << ", " << pos.y);
	//_pWeaponObject->GetTransform()->SetPosition(pos);

	if (!_pDay->IsDay())
	{
		_pWaveController->TryNewWave();
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

	_pStartButton = new GameObject("BUTTON", "UI");
	_pStartButton->AddComponent(new Button(_pStartButton));
	_pStartButton->AddComponent(new BoxColliderComponent(_pStartButton));
	//_pStartButton->AddComponent(new TextComponent(_pTestObject));

	_pStartButton->AddComponent(ResourceManager::GetTexture("Button"));

	AddGameObject(_pStartButton);

	_pStartButton->GetTransform()->SetPosition(0.0f, 0.0f);
	_pStartButton->GetTransform()->SetScale({ 0.2f, 0.2f });


	_pWeaponObject = new GameObject("Weapon");
	_pWeaponObject->AddComponent<Texture2D>(ResourceManager::GetTexture("swords"));
	_pWeaponObject->GetTransform()->SetScale({0.20f, 0.20f});
	_pWeaponObject->GetTransform()->SetPosition({1.5f, 0.0f});
	SpriteComponent* pWeaponSC = _pWeaponObject->AddComponent<SpriteComponent>(new SpriteComponent(_pWeaponObject));

	AnimatedSpritesheet* pWeaSS = new AnimatedSpritesheet(ResourceManager::GetTexture("swords"), 16, 16, false);
	pWeaponSC->SetSprite(pWeaSS->GetSpriteAtIndex(6));

	AddGameObject(_pWeaponObject);

	_pPlayer = new Player();
	AddGameObject(_pPlayer);

	_pTilemap = new TileMap(_name);

	_pWaveController = new WaveController(this);

	_pDay = new Day();
	_pDay->SetWaveController(_pWaveController);
}
