#include "Character.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"

Character::Character(std::string texture, std::string name, std::string tag) 
	: GameObject(name, tag) 
{
	AddComponent(ResourceManager::GetTexture(texture));
	_pAnimSheet = new AnimatedSpritesheet(ResourceManager::GetTexture(texture), 16, 32, "AnimatedCharacter");


	_pMovement = AddComponent(new MovementComponent(this));
	_pMovement->SetMovementSpeed(1.0f);
	_pSc = AddComponent<SpriteComponent>(new SpriteComponent(this));
	_pSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(0));
	_pAnimSheet->SetFramerate(4);
	_pTransform->SetScale({ 0.25f, 0.45f });
}

void Character::UniqueLogic()
{
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
