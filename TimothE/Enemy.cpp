#include "Enemy.h"
#include "AIController.h"
#include "AIMovementCompnent.h"
#include "EnemyHealth.h"
#include "Fighter.h"
#include "WeaponObject.h"
#include "SceneManager.h"

Enemy::Enemy(std::string name, std::string tag)
	: Character(name, tag)
{
	_pMover = AddComponent(new AIMovementCompnent(this, SceneManager::GetCurrentScene()->GetAStar()));

	_pWeapon = new WeaponObject();
	_pWeapon->SetParent(this);
	SceneManager::GetCurrentScene()->AddGameObject(_pWeapon);

	_pController = AddComponent(new AIController(this));
	_pFighter = AddComponent(new Fighter(this));
	_pHealth = AddComponent(new EnemyHealth(this, 50));

	AddComponent(new BoxColliderComponent(this))->SetTrigger(true);

	_pMover->SetAllowCollisions(false);

	_pMovement = _pMover;

	_pController->SetTargetTags("WALL", "TOWER", "CROPS");

}

void Enemy::UniqueLogic()
{
	Character::UniqueLogic();
}
