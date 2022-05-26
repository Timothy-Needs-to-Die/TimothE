#include "Player.h"
#include "PlayerInputComponent.h"
#include "PlayerHealth.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "SceneManager.h"
#include "WeaponObject.h"
#include "PlayerUIComponent.h"

Player::Player(std::string name /*= "Player"*/, std::string tag /*= "PLAYER"*/)
	: Character(name, tag)
{
	_pInput = AddComponent(new PlayerInputComponent(this));

	_pWeapon = new WeaponObject();
	_pWeapon->SetParent(this);
	SceneManager::GetCurrentScene()->AddGameObject(_pWeapon);

	_pHealth = AddComponent(new PlayerHealth(this, 100));
	_pFighter = AddComponent(new Fighter(this));
	_pCollider = AddComponent(new BoxColliderComponent(this));
	_pCollider->SetTrigger(true);

	_pUI = AddComponent(new PlayerUIComponent(this));
}

void Player::UniqueLogic()
{
	Character::UniqueLogic();
}
