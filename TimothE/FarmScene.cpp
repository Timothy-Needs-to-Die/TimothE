#include "FarmScene.h"
#include "Button.h"
#include "SpriteComponent.h"

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


}

void FarmScene::InitScene()
{
	_pAnimSheet = new AnimatedSpritesheet(ResourceManager::GetTexture("character"), 16, 32);
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

	_pPlayerObject = new GameObject("Player", ObjectType::Player);
	_pMovement = _pPlayerObject->AddComponent(new MovementComponent(_pPlayerObject));
	_pMovement->SetMovementSpeed(1.0f);
	_pPlayerObject->AddComponent(new Fighter(_pPlayerObject));
	_pPlayerMovement = new PlayerInputComponent(_pPlayerObject);
	
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

	GameObject* enemyGO = new GameObject("Enemy", ObjectType::Enemy);
	enemyGO->AddComponent<Texture2D>(new Texture2D(enemyGO));
	enemyGO->GetTransform()->SetPosition(2.0f, 2.0f);
	enemyGO->GetTransform()->SetScale({ 0.25f, 0.45f });

	_pEnemyHealth = enemyGO->AddComponent(new Health(enemyGO));
	_pEnemyHealth->SetMaxHealth(50);
	AddGameObject(enemyGO);

	
}
