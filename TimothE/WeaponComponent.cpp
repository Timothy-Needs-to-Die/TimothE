#include "pch.h"
#include "WeaponComponent.h"
#include "AnimatedSpritesheet.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"

WeaponComponent::WeaponComponent(GameObject* object)
	: Component(object)
{
	SetType(Component::Weapon_Type);

	_pAnimSheet = new AnimatedSpritesheet(ResourceManager::GetTexture("swords"), 16, 16, "Swords");
	_pSprite = _pParentObject->AddComponent<SpriteComponent>(new SpriteComponent(_pParentObject, 90));
	_pSprite->SetSprite(_pAnimSheet->GetSpriteAtIndex(_currentLevel));
	_pAnimSheet->SetFramerate(2);
}

void WeaponComponent::OnStart()
{
}

void WeaponComponent::OnUpdate()
{
}

void WeaponComponent::OnEnd()
{
}

void WeaponComponent::StartAttack()
{
	_pSprite->SetSprite(_pAnimSheet->GetSpriteAtIndex(_currentLevel));
}

void WeaponComponent::EndAttack()
{
	_pSprite->SetSprite(_pAnimSheet->GetSpriteAtIndex(_currentLevel + _amountOfLevels));
}
