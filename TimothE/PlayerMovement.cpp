#include "PlayerMovement.h"
#include "CameraManager.h"

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

		if (newPos.y < 0.0f) newPos.y = 0.0f;
	}

	if (Input::IsKeyDown(KEY_A)) {
		newPos.x -= 2.0f * deltaTime;

		if (newPos.x < 0.0f) newPos.x = 0.0f;
	}
	else if (Input::IsKeyDown(KEY_D)) {
		newPos.x += 2.0f * deltaTime;
	}

	ColQuad playerQuad;
	playerQuad.pos = newPos;
	playerQuad.size = { 0.25f, 0.25f };

	for (float x = newPos.x - 0.25f; x <= newPos.x + 0.25f; x += 0.25f) {
		for (float y = newPos.y - 0.25f; y <= newPos.y + 0.25f; y += 0.25f) {
			glm::vec2 pos = { x,y };
			TileData* tile = _pTileMap->GetTileAtWorldPos(pos);

			ColQuad tileQuad;
			tileQuad.pos = { tile->colXPos, tile->colYPos };
			tileQuad.size = glm::vec2(tile->size, tile->size);

			if (tile->collidable) {
				if (Physics::Intersects(playerQuad, tileQuad)) {
					newPos = transform->GetPosition();
				}
			}
		}
	}

	transform->SetPosition(newPos.x, newPos.y);
	CameraManager::GetCamera(-1)->SetPosition({ newPos.x, newPos.y, -1.0f });
}

void PlayerMovement::OnEnd()
{

}
