#include "pch.h"
#include "MovementComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "TileMap.h"
#include "Time.h"
#include "SceneManager.h"


MovementComponent::MovementComponent(GameObject* gameObject) : Component(gameObject)
{
	_direction = Direction::STATIONARY;
	_moving = false;
	SetType(Types::Movement);

	_pTilemap = SceneManager::GetCurrentScene()->GetTileMap();
}

void MovementComponent::Move(glm::vec2 moveVec)
{
	// if magnitude greater than 1 (moving diagonally), normalize to prevent moving at double speed
	float mag = sqrt((moveVec.x * moveVec.x) + (moveVec.y * moveVec.y));
	if (mag > 1.0f)
	{
		moveVec.x /= mag;
		moveVec.y /= mag;
	}

	_moving = (moveVec.x == 0.0f && moveVec.y == 0.0f) ? false : true;
	if (!_moving) return;


	DecideDirection(moveVec);


	Transform* transform = _pParentObject->GetTransform();
	glm::vec2 originalPosition = transform->GetPosition();
	glm::vec2 newPos = originalPosition;

	newPos += moveVec * _movementSpeed * (float)Time::GetDeltaTime();

	if (_allowCollisions) {
		CollisionCheck(newPos);
	}


	transform->SetPosition(newPos);
}

void MovementComponent::CollisionCheck(glm::vec2& newPos)
{
	glm::vec2 mapSize = SceneManager::GetCurrentScene()->GetTileMap()->GetMapSize();
	glm::vec2 parentScale = _pParentObject->GetTransform()->GetScale();


	if (newPos.x < 0.0f) {
		newPos.x = 0.0f;
	}

	if (newPos.y < 0.0f) {
		newPos.y = 0.0f;
	}


	//These values should be retrieved from the tilemap
	if (newPos.y + parentScale.y > mapSize.y) {
		newPos.y = mapSize.y - parentScale.y;
	}

	if (newPos.x + parentScale.x > mapSize.x) {
		newPos.x = mapSize.x - parentScale.x;
	}


	ColQuad playerQuad;
	playerQuad.pos = newPos;

	playerQuad.size = parentScale;
	playerQuad.size.y /= 2.0f;
	playerQuad.CalculateMax();
	
	TileData* tile = _pTilemap->GetTileAtWorldPos(0, newPos);
	//TIM_LOG_LOG("Player Tile Pos: " << tile->pos.x << ", " << tile->pos.y);

	
	float tileSize = 1.0f / _pTilemap->GetTilesPerUnit();

	for (float x = newPos.x - tileSize; x <= newPos.x + tileSize; x += tileSize) {
		for (float y = newPos.y - tileSize; y <= newPos.y + tileSize; y += tileSize) {
			glm::vec2 pos = { x,y };

			bool collidable = _pTilemap->CollidableAtPosition(pos);
			if (collidable) {
				TileData* tile = _pTilemap->GetTileAtWorldPos(0, pos);

				ColQuad tileQuad;
				tileQuad.pos = tile->pos;
				tileQuad.size = glm::vec2(tile->size, tile->size);
				tileQuad.CalculateMax();

				if (Physics::Intersects(playerQuad, tileQuad)) {

					float dx1 = tileQuad.pos.x - playerQuad.max.x;
					float dx2 = tileQuad.max.x - playerQuad.pos.x;
					float dy1 = tileQuad.pos.y - playerQuad.max.y;
					float dy2 = tileQuad.max.y - playerQuad.pos.y;

					float dx = (abs(dx1) < abs(dx2)) ? dx1 : dx2;
					float dy = (abs(dy1) < abs(dy2)) ? dy1 : dy2;

					if (abs(dx) <= abs(dy)) {
						newPos.x += dx;
					}
					else if (abs(dy) <= abs(dx)) {
						newPos.y += dy;
					}
				}
			}
		}
	}




}

void MovementComponent::DecideDirection(glm::vec2& moveVec)
{
	glm::vec2 newForward = glm::vec2(0.0f);
	float xVal;

	//If the x value is greater than or equal to y value
	if (moveVec.x >= moveVec.y) {
		//We are moving left or right. Decide based on if the x component is greater than 0
		_direction = moveVec.x > 0.0f ? Direction::RIGHT : Direction::LEFT;

		if (_direction == Direction::LEFT) {
			newForward.x = 0.0f;
			newForward.y = -1.0f;
		}
		else {
			newForward.x = 1.0f;
			newForward.y = 0.0f;
		}
	}
	else {
		//We are moving up or down. Decide based on if the y component is greater than 0
		_direction = moveVec.y > 0.0f ? Direction::UP : Direction::DOWN;

		if (_direction == Direction::UP) {
			newForward.x = 0.0f;
			newForward.y = 1.0f;
		}
		else {
			newForward.x = -1.0f;
			newForward.y = 0.0f;
		}
	}

	
	newForward = glm::normalize(newForward);
	_pParentObject->GetTransform()->SetForward(newForward);
}

void MovementComponent::OnStart()
{

}

void MovementComponent::OnUpdate()
{
	if (_constantlyMove) {
		Move(_desiredDirection);
	}
}

void MovementComponent::OnEnd()
{

}
