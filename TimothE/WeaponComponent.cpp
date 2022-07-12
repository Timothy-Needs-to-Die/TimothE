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

	_pSprite = _pParentObject->AddComponent<SpriteComponent>(new SpriteComponent(_pParentObject, 90));
	_pSprite->SetSprite(ResourceManager::GetSpriteSheet("swords_new")->GetSpriteAtIndex(0));
	_pSprite->SetEnabled(false);
}

void WeaponComponent::OnUpdate()
{
	if (_swinging) {
		float currentRot = _pParentObject->GetTransform()->GetRotation();
		currentRot -= 185.0f * Time::GetDeltaTime();
		_pParentObject->GetTransform()->SetRotation(currentRot);

		glm::vec2 currentPos = _pParentObject->GetTransform()->GetPosition();
		currentPos.x += 0.1f * Time::GetDeltaTime();
		_pParentObject->GetTransform()->SetPosition(currentPos);
	}
}

void WeaponComponent::StartAttack()
{

	_pSprite->SetEnabled(true);
	_pParentObject->GetTransform()->SetRotation(80.0f);

	_originalPosition = _pParentObject->GetTransform()->GetPosition();

	_swinging = true;
}

void WeaponComponent::EndAttack()
{
	_pSprite->SetEnabled(false);
	_pParentObject->GetTransform()->SetRotation(80.0f);
	
	_pParentObject->GetTransform()->SetPosition(_originalPosition);

	_swinging = false;
}
