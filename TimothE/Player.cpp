#include "Player.h"
#include "PlayerInputComponent.h"
#include "PlayerHealth.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"

Player::Player(std::string name /*= "Player"*/, std::string tag /*= "PLAYER"*/)
	: Character(name, tag)
{
	_pInput = AddComponent(new PlayerInputComponent(this));
	_pHealth = AddComponent(new PlayerHealth(this, 100));
	_pFighter = AddComponent(new Fighter(this));
	_pCollider = AddComponent(new BoxColliderComponent(this));
	_pCollider->SetTrigger(true);
	_pFarmlandManager = AddComponent(new FarmlandManager(this));
}

void Player::UniqueLogic()
{
	Character::UniqueLogic();
}
