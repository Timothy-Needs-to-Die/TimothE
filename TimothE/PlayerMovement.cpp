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

		if (newPos.y < 0.0f) newPos.y = 0.0f;
	}

	if (Input::IsKeyDown(KEY_A)) {
		newPos.x -= 2.0f * deltaTime;

		if (newPos.x < 0.0f) newPos.x = 0.0f;
	}
	else if (Input::IsKeyDown(KEY_D)) {
		newPos.x += 2.0f * deltaTime;
	}

	glm::vec2 leftPos = { newPos.x - 0.25f, newPos.y };
	glm::vec2 rightPos = { newPos.x + 0.25f, newPos.y };
	glm::vec2 topPos = { newPos.x, newPos.y + 0.25f };
	glm::vec2 bottomPos = { newPos.x, newPos.y - 0.25f };

	TileData* leftTile = _pTileMap->GetTileAtWorldPos(leftPos);
	TileData* rightTile = _pTileMap->GetTileAtWorldPos(rightPos);
	TileData* topTile = _pTileMap->GetTileAtWorldPos(topPos);
	TileData* bottomTile = _pTileMap->GetTileAtWorldPos(bottomPos);

	ColQuad playerQuad;
	playerQuad.pos = newPos;
	playerQuad.size = { 0.25f, 0.25f };

	if (leftTile->collidable) {
		ColQuad lt;
		lt.pos = { leftTile->colXPos, leftTile->colYPos };
		lt.size = glm::vec2(leftTile->size, leftTile->size);
		if (Physics::Intersects(playerQuad, lt)) {
			std::cout << "Left Tile" << std::endl;
			newPos.x = transform->GetPosition().x;
		}
	}
	if (rightTile->collidable) {
		ColQuad rt;
		rt.pos = { rightTile->colXPos, rightTile->colYPos };
		rt.size = glm::vec2(rightTile->size, rightTile->size);
		std::cout << "Testing RT" << std::endl;
		if (Physics::Intersects(playerQuad, rt)) {
			std::cout << "Right Tile" << std::endl;
			newPos.x = transform->GetPosition().x;
		}
	}
	if (topTile->collidable) {
		ColQuad tt;
		tt.pos = { topTile->colXPos, topTile->colYPos };
		tt.size = glm::vec2(topTile->size, topTile->size);
		if (Physics::Intersects(playerQuad, tt)) {
			newPos.y = transform->GetPosition().y;
			std::cout << "Top Tile" << std::endl;
		}
	}
	if (bottomTile->collidable) {
		ColQuad bt;
		bt.pos = { bottomTile->colXPos, bottomTile->colYPos };
		bt.size = glm::vec2(bottomTile->size, bottomTile->size);
		if (Physics::Intersects(playerQuad, bt)) {
			newPos.y = transform->GetPosition().y;
			std::cout << "Bottom Tile" << std::endl;
		}
	}

	transform->SetPosition(newPos.x, newPos.y);
}

void PlayerMovement::OnEnd()
{

}
