#include "PlayerInputComponent.h"
#include "CameraManager.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"

void PlayerInputComponent::OnStart()
{
	_pMovement = _pParentObject->GetComponent<MovementComponent>();
	_pFighter = _pParentObject->GetComponent<Fighter>();
}

void PlayerInputComponent::OnUpdate()
{
	if (_pMovement == nullptr) {
		std::cout << "[ERROR: PlayerInputComponent::OnUpdate]: Player does not have movement component attached" << std::endl;
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
		std::cout << "[ERROR: PlayerInputComponent::OnUpdate]: Player does not have fighter component attached" << std::endl;
		return;
	}

	if (Input::IsKeyDown(KEY_SPACE)) {
		_pFighter->Attack();
	}
}

void PlayerInputComponent::OnEnd()
{

}
