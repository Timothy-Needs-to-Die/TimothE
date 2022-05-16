#include "FarmScene.h"
#include "Button.h"
#include "SpriteComponent.h"

FarmScene::~FarmScene()
{
	
}

void FarmScene::UpdateUI()
{

}

void FarmScene::UpdateObjects()
{
	Scene::UpdateObjects();

	_pAnimSheet->Update();

	int currentRow = _pAnimSheet->GetCurrentRow();

	Direction playerDirection = _pMovement->GetDirection();

	switch (playerDirection)
	{
	case Direction::UP:
		currentRow = 1;
		break;
	case Direction::DOWN:
		currentRow = 0;
		break;
	case Direction::LEFT:
		currentRow = 3;
		break;
	case Direction::RIGHT:
		currentRow = 2;
		break;
	default:
		break;
	}

	if (currentRow != _pAnimSheet->GetCurrentRow()) {
		_pAnimSheet->SetCurrentRow(currentRow);
	}

	_pAnimSheet->SetStationary(!_pMovement->IsMoving());
	_pSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(_pAnimSheet->GetCurrentIndex()));

	glm::vec2 forward = _pPlayerObject->GetTransform()->GetForward();
	glm::vec2 pos = forward * 0.25f;

	//TIM_LOG_LOG("Player forward: " << forward.x << ", " << forward.y);
	//TIM_LOG_LOG("Weapon Pos: " << pos.x << ", " << pos.y);
	_pWeaponObject->GetTransform()->SetPosition(pos);

	if (_pDay->NightStart())
	{
		_pWaveController->SpawnWave(5);

		for (GameObject* go : _pWaveController->GetEnemies())
		{
			AddGameObject(go);
		}
	}
	//std::cout << _pPlayerObject->GetTransform()->GetPosition().x << ", " << _pPlayerObject->GetTransform()->GetPosition().y << std::endl;
}

void FarmScene::InitScene()
{
	_listOfGameObjects.clear();
	_listOfDrawableGameObjects.clear();

	_pAnimSheet = new AnimatedSpritesheet(ResourceManager::GetTexture("character"), 16, 32);
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

	_pPlayerObject = new GameObject("Player", "PLAYER");
	_pMovement = _pPlayerObject->AddComponent(new MovementComponent(_pPlayerObject));
	_pMovement->SetMovementSpeed(1.0f);
	_pPlayerObject->AddComponent(new Fighter(_pPlayerObject));
	_pPlayerMovement = new PlayerInputComponent(_pPlayerObject);

	_pWeaponObject = new GameObject("Weapon");
	_pWeaponObject->SetParent(_pPlayerObject);
	_pWeaponObject->AddComponent<Texture2D>(ResourceManager::GetTexture("character"));
	_pWeaponObject->GetTransform()->SetScale({0.25f, 0.15f});
	_pWeaponObject->GetTransform()->SetPosition({1.5f, 0.0f});
	AddGameObject(_pWeaponObject);


	_pPlayerObject->AddComponent(_pPlayerMovement);
	_pPlayerObject->AddComponent(ResourceManager::GetTexture("character"));
	_pSc = _pPlayerObject->AddComponent<SpriteComponent>(new SpriteComponent(_pPlayerObject));
	_pAnimSheet->SetFramerate(4);
	_pPlayerObject->GetTransform()->SetScale({ 0.25f, 0.45f });
	AddGameObject(_pPlayerObject);

	_pTilemap = new TileMap(_name);

	_pSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(0));
	//_pTilemap->SetSpriteSheet(ResourceManager::GetSpriteSheet("testSheet"));
	//_pTilemap->LoadTileMap();

	_pWaveController = new WaveController(this);
}
