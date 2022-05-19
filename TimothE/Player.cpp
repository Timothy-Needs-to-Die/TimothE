#include "Player.h"
#include "PlayerInputComponent.h"
#include "Health.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"

Player::Player(std::string name /*= "Player"*/, std::string tag /*= "PLAYER"*/)
	: Character(name, tag)
{
	_pInput = AddComponent(new PlayerInputComponent(this));
	_pHealth = AddComponent(new Health(this));
	_pFighter = AddComponent(new Fighter(this));
	_pCollider = AddComponent(new BoxColliderComponent(this));
	_pCollider->SetTrigger(true);
}

void Player::UniqueLogic()
{
	Character::UniqueLogic();


}
