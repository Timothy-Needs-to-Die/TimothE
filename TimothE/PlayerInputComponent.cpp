#include "PlayerInputComponent.h"
#include "CameraManager.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "ResourceNode.h"
#include "PlayerResourceManager.h"
#include "PurchaseableConfig.h"

void PlayerInputComponent::OnStart()
{
	_pMovement = _pParentObject->GetComponent<MovementComponent>();
	_pFighter = _pParentObject->GetComponent<Fighter>();
}

void PlayerInputComponent::OnUpdate()
{
	if (_pMovement == nullptr) {
		TIM_LOG_ERROR("Character does not have movement component attached");
		return;
	}

	glm::vec2 moveVec = glm::vec2(0.0f);

	if (Input::IsKeyHeld(KEY_W)) {
		moveVec.y = 1.0f;
	}
	else if (Input::IsKeyHeld(KEY_S)) {
		moveVec.y = -1.0f;
	}

	if (Input::IsKeyHeld(KEY_A)) {
		moveVec.x = -1.0f;
	}
	else if (Input::IsKeyHeld(KEY_D)) {
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
		if (Input::IsMouseButtonDown(BUTTON_1)) {
			_pNearbyResourceNode->Interact();
		}
	}

	if (Input::IsKeyDown(KEY_R)) {
		int goldAmount = PlayerResourceManager::GetCoreResource(CoreResourceType::Gold)->GetAmount();
		int woodAmount = PlayerResourceManager::GetCoreResource(CoreResourceType::Wood)->GetAmount();
		int metalAmount = PlayerResourceManager::GetCoreResource(CoreResourceType::Metal)->GetAmount();
		int stoneAmount = PlayerResourceManager::GetCoreResource(CoreResourceType::Stone)->GetAmount();

		TIM_LOG_LOG("Gold: " << goldAmount);
		TIM_LOG_LOG("Wood: " << woodAmount);
		TIM_LOG_LOG("Metal: " << metalAmount);
		TIM_LOG_LOG("Stone: " << stoneAmount);
	}

	if (Input::IsKeyDown(KEY_1)) {
		ResourceCost wallCost;
		wallCost.woodRequired = 1;

		if (PlayerResourceManager::CanAfford(wallCost)) {
			TIM_LOG_LOG("Can Afford Wall");
		}
		else {
			TIM_LOG_LOG("Can't Afford Wall");
		}
	}

	if (Input::IsKeyDown(KEY_2)) {
		ResourceCost towerCost;
		towerCost.woodRequired = 3;
		towerCost.stoneRequired = 5;

		if (PlayerResourceManager::CanAfford(towerCost)) {
			TIM_LOG_LOG("Can Afford Tower");
		}
		else{
			TIM_LOG_LOG("Can't Afford Tower");
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
		TIM_LOG_LOG("OnTriggerEnter");
		_pNearbyResourceNode = other->GetParent()->GetComponent<ResourceNode>();
	}
}

void PlayerInputComponent::OnTriggerExit(ColliderBase* other)
{
	if (other->GetParent()->GetTag() == "RESOURCE_NODE") {
		TIM_LOG_LOG("OnTriggerExit");
		_pNearbyResourceNode = nullptr;
	}
}
