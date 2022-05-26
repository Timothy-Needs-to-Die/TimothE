#include "Player.h"
#include "PlayerInputComponent.h"
#include "PlayerHealth.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "TextComponent.h"
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

	
	_pFighter = AddComponent(new Fighter(this));
	_pCollider = AddComponent(new BoxColliderComponent(this));
	_pCollider->SetTrigger(true);

	_pUI = AddComponent(new PlayerUIComponent(this));
	_pInteractableUI = AddComponent(new TextComponent(this));
	_pInteractableUI->SetText("Interactable");
	_pHealth = AddComponent(new PlayerHealth(this, 100));

	_pHealthObj = new GameObject("PlayerHealth", "UI");
	_pHealthUI = _pHealthObj->AddComponent(new TextComponent(_pHealthObj));
	_pHealthObj->GetTransform()->SetPosition(1600.0f, 1000.0f);
	SceneManager::GetCurrentScene()->AddGameObject(_pHealthObj);
}

void Player::UniqueLogic()
{
	Character::UniqueLogic();
	DisplayPlayerUI();
}

void Player::DisplayPlayerUI()
{
	_pHealthUI->SetText("Health: " + std::to_string(_pHealth->GetCurrentHealth()));
}
