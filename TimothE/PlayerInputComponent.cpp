#include "PlayerInputComponent.h"
#include "CameraManager.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "ResourceNode.h"

void PlayerInputComponent::OnStart()
{
	_pMovement = _pParentObject->GetComponent<MovementComponent>();
	_pFighter = _pParentObject->GetComponent<Fighter>();
}

void PlayerInputComponent::OnUpdate()
{
	if (_pMovement == nullptr) {
		TIM_LOG_ERROR("Player does not have movement component attached");
		return;
	}

	glm::vec2 moveVec = glm::vec2(0.0f);

	if (Input::IsKeyDown(KEY_W)) {
		moveVec.y = 1.0f;
	}
	else if (Input::IsKeyDown(KEY_S)) {
		moveVec.y = -1.0f;
	}

	if (Input::IsKeyDown(KEY_A)) {
		moveVec.x = -1.0f;
	}
	else if (Input::IsKeyDown(KEY_D)) {
		moveVec.x = 1.0f;
	}

	_pMovement->Move(moveVec);

	CameraManager::GetCamera(-1)->SetPosition({ _pParentObject->GetTransform()->GetPosition(), -2.0f });

	if (_pFighter == nullptr) {
		TIM_LOG_ERROR("Player does not have fighter component attached");
		return;
	}

	if (Input::IsKeyDown(KEY_SPACE)) {
		_pFighter->Attack();
	}

	if (_pNearbyResourceNode != nullptr) {
		if (Input::IsKeyDown(KEY_E)) {
			_pNearbyResourceNode->Interact();
		}
	}
}

void PlayerInputComponent::OnEnd()
{

}

void PlayerInputComponent::NearbyResourceNode(class ResourceNode* nearbyResource)
{
	_pNearbyResourceNode = nearbyResource;
}

void PlayerInputComponent::OnTriggerEnter(ColliderBase* other)
{
	if (other->GetParent()->GetTag() == "RESOURCE_NODE") {
		_pNearbyResourceNode = other->GetParent()->GetComponent<ResourceNode>();
	}
}
