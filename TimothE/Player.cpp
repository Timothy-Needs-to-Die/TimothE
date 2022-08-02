#include "pch.h"
#include "Player.h"
#include "PlayerInputComponent.h"
#include "PlayerHealth.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "SceneManager.h"
#include "WeaponObject.h"
#include "PlayerUIComponent.h"
#include "TextComponent.h"
#include "Fighter.h"
#include "FarmlandManager.h"

Player::Player(std::string name /*= "Player"*/, std::string tag /*= "PLAYER"*/)
	: Character("PlayerSheet_Updated.png", name, tag)
{
	_pInput = AddComponent(new PlayerInputComponent(this));

	_pWeapon = new WeaponObject();
	_pWeapon->SetOwner(this);

	_pWeapon->GetTransform()->SetPosition({ 0.0f, 0.38f });
	_pWeapon->GetTransform()->SetScale({ 0.5f, 0.25f });
	SceneManager::GetCurrentScene()->AddGameObject(_pWeapon);

	//_pHealth = AddComponent(new PlayerHealth(this, 100));
	_pFighter = AddComponent(new Fighter(this));
	_pCollider = AddComponent(new BoxColliderComponent(this));
	_pCollider->SetTrigger(true);
	_pFarmlandManager = AddComponent(new FarmlandManager(this));
	
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
