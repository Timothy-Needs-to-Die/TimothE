#include "pch.h"
#include "Enemy.h"
#include "AIController.h"
#include "AIMovementCompnent.h"
#include "EnemyHealth.h"
#include "Fighter.h"
#include "WeaponObject.h"
#include "SceneManager.h"
#include "BoxColliderComponent.h"

Enemy::Enemy(std::string name, std::string tag)
	: Character("PlayerSheet_Updated.png", name, tag)
{
	_pMover = AddComponent(new AIMovementCompnent(this, SceneManager::GetCurrentScene()->GetAStar()));

	_pWeapon = new WeaponObject();
	_pWeapon->SetParent(this);
	SceneManager::GetCurrentScene()->AddGameObject(_pWeapon);

	_pController = AddComponent(new AIController(this));
	_pFighter = AddComponent(new Fighter(this));
	_pHealth = AddComponent(new EnemyHealth(this, 50));

	BoxColliderComponent* pBox = AddComponent(new BoxColliderComponent(this));
	pBox->SetTrigger(true);
	pBox->SetCollidersChannel(CollisionChannel_Enemy);
	pBox->AddCompatibleChannel(CollisionChannel_Player);
	//pBox->AddCompatibleChannel(CollisionChannel_Enemy);


	_pMover->SetAllowCollisions(false);

	_pMovement = _pMover;

	_pController->SetTargetTags("WALL", "TOWER", "CROPS");

}

void Enemy::UniqueLogic()
{
	Character::UniqueLogic();
}
