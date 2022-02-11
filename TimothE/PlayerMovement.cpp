#include "PlayerMovement.h"

void PlayerMovement::OnStart()
{

}

void PlayerMovement::OnUpdate(float deltaTime)
{
	Transform* transform = _pParentObject->GetTransform();
	glm::vec2 newPos = transform->GetPosition();

	if (Input::IsKeyDown(KEY_W)) {
		newPos.y += 2.0f * deltaTime;
	}
	else if (Input::IsKeyDown(KEY_S)) {
		newPos.y -= 2.0f * deltaTime;
	}

	if (Input::IsKeyDown(KEY_A)) {
		newPos.x -= 2.0f * deltaTime;
	}
	else if (Input::IsKeyDown(KEY_D)) {
		newPos.x += 2.0f * deltaTime;
	}

	transform->SetPosition(newPos.x, newPos.y);
}

void PlayerMovement::OnEnd()
{

}
