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

	_pSprite = _pOwner->AddComponent<SpriteComponent>(new SpriteComponent(_pOwner, 120));
	_pSprite->SetSprite(ResourceManager::GetSpriteSheet("swords_new")->GetSpriteAtIndex(0));
	_pSprite->SetEnabled(false);

	_positionEachFrame[0] = glm::vec2{ -0.2f, 0.3f};
	_positionEachFrame[1] = glm::vec2{ -0.15f, 0.35f};
	_positionEachFrame[2] = glm::vec2{ -0.10f, 0.35f};
	_positionEachFrame[3] = glm::vec2{ -0.05f, 0.30f};

	//TODO: Rotation values
	_rotationEachFrame[0] = 0.0f;
	_rotationEachFrame[1] = -15.0f;
	_rotationEachFrame[2] = -30.0f;
	_rotationEachFrame[3] = -50.0f;

}

void WeaponComponent::OnUpdate()
{
	//if (_swinging) {
	//	float currentRot = _pOwner->GetTransform()->GetRotation();
	//	currentRot -= 185.0f * Time::GetDeltaTime();
	//	_pOwner->GetTransform()->SetRotation(currentRot);
	//
	//	glm::vec2 currentPos = _pOwner->GetTransform()->GetPosition();
	//	currentPos.x += 0.1f * Time::GetDeltaTime();
	//	_pOwner->GetTransform()->SetPosition(currentPos);
	//}
}

void WeaponComponent::StartAttack()
{

	_pSprite->SetEnabled(true);
	//_pOwner->GetTransform()->SetRotation(80.0f);

	//_originalPosition = _pOwner->GetTransform()->GetPosition();

	_swinging = true;
}

void WeaponComponent::EndAttack()
{
	_pSprite->SetEnabled(false);
	//_pOwner->GetTransform()->SetRotation(80.0f);
	
	//_pOwner->GetTransform()->SetPosition(_originalPosition);

	_swinging = false;
}

void WeaponComponent::IncrementFrame()
{
	_currentFrame = (_currentFrame + 1) % _numberOfFrames;
	_pOwner->GetTransform()->SetPosition(_positionEachFrame[_currentFrame]);
	_pOwner->GetTransform()->SetRotation(_rotationEachFrame[_currentFrame]);

	//TODO: Rotation
}

void WeaponComponent::ResetFrames()
{
	_currentFrame = 0;
	_pOwner->GetTransform()->SetPosition(_positionEachFrame[_currentFrame]);
	_pOwner->GetTransform()->SetRotation(_rotationEachFrame[_currentFrame]);
}

void WeaponComponent::SetToFrame(int val)
{
	_currentFrame = val;
	_pOwner->GetTransform()->SetPosition(_positionEachFrame[_currentFrame]);
	_pOwner->GetTransform()->SetRotation(_rotationEachFrame[_currentFrame]);
}
