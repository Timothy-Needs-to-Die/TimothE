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

	//_pAnimSheet = new AnimatedSpritesheet(ResourceManager::GetTexture("swords.png"), 16, 16);
	_pSprite = _pParentObject->AddComponent<SpriteComponent>(new SpriteComponent(_pParentObject, 90));
	_pSprite->SetSprite(ResourceManager::GetSpriteSheet("swords_new")->GetSpriteAtIndex(0));


	_pParentObject->GetTransform()->SetPosition({ 0.0f, 1.6f });
	
	//_pAnimSheet->SetFramerate(2);
}

void WeaponComponent::OnStart()
{
}

void WeaponComponent::OnUpdate()
{
	if (_swinging) {
		float currentRot = _pParentObject->GetTransform()->GetRotation();

		currentRot -= 105.0f * Time::GetDeltaTime();

		_pParentObject->GetTransform()->SetRotation(currentRot);
	}
}

void WeaponComponent::OnEnd()
{
}

void WeaponComponent::StartAttack()
{
	_pParentObject->GetTransform()->SetRotation(-20.0f);

	_swinging = true;

	//_pSprite->SetSprite(_pAnimSheet->GetSpriteAtIndex(_currentLevel));
}

void WeaponComponent::EndAttack()
{
	_pParentObject->GetTransform()->SetRotation(0.0f);

	_swinging = false;

	//_pSprite->SetSprite(_pAnimSheet->GetSpriteAtIndex(_currentLevel + _amountOfLevels));
}
