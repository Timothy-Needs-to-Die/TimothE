#include "Enemy.h"
#include "AIController.h"
#include "AIMovementCompnent.h"
#include "EnemyHealth.h"
#include "Fighter.h"

Enemy::Enemy(std::string name, std::string tag)
	: Character(name, tag)
{
	_pMover = AddComponent(new AIMovementCompnent(this, SceneManager::GetCurrentScene()->GetAStar()));

	_pController = AddComponent(new AIController(this));
	_pFighter = AddComponent(new Fighter(this));
	_pHealth = AddComponent(new EnemyHealth(this, 50));

	_pMover->SetAllowCollisions(false);

	_pMovement = _pMover;

	_pController->SetTargetTags("WALL", "TOWER", "CROPS");
}

void Enemy::UniqueLogic()
{
	Character::UniqueLogic();
}
