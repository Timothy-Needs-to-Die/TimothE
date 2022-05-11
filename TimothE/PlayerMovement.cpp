#include "PlayerMovement.h"
#include "CameraManager.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"

void PlayerMovement::OnStart()
{
	_pMovement = _pParentObject->GetComponent<MovementComponent>();
}

void PlayerMovement::OnUpdate()
{
	if (_pMovement == nullptr) {
		std::cout << "[ERROR: PlayerMovement::OnUpdate]: Player does not have movement component attached" << std::endl;
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

	CameraManager::GetCamera(-1)->SetPosition({ _pParentObject->GetTransform()->GetPosition(), -1.0f });
}

void PlayerMovement::OnEnd()
{

}
