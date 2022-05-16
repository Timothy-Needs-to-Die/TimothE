#include "Player.h"
#include "PlayerInputComponent.h"
#include "Health.h"
#include "GameObject.h"

Player::Player(std::string name /*= "Player"*/, std::string tag /*= "PLAYER"*/)
	: Character(name, tag)
{
	_pPlayerMovement = AddComponent(new PlayerInputComponent(this));
	_pHealth = AddComponent(new Health(this));
	_pFighter = AddComponent(new Fighter(this));
}

void Player::UniqueLogic()
{
	Character::UniqueLogic();


}
