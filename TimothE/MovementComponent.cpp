#include "MovementComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "TileMap.h"
#include "Time.h"
#include "SceneManager.h"


void MovementComponent::Move(glm::vec2 moveVec)
{
	// if magnitude greater than 1 (moving diagonally), normalise to prevent moving at double speed
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

	CollisionCheck(newPos);


	transform->SetPosition(newPos);
}

void MovementComponent::CollisionCheck(glm::vec2& newPos)
{
	if (newPos.x < 0.0f) {
		newPos.x = 0.0f;
	}

	if (newPos.y < 0.0f) {
		newPos.y = 0.0f;
	}

	TileMap* pTilemap = SceneManager::GetCurrentScene()->GetTileMap();

	ColQuad playerQuad;
	playerQuad.pos = newPos;

	playerQuad.size = _pParentObject->GetTransform()->GetScale();
	playerQuad.size.y /= 2.0f;
	playerQuad.CalculateMax();
	


	for (float x = newPos.x - 0.25f; x <= newPos.x + 0.25f; x += 0.25f) {
		for (float y = newPos.y - 0.25f; y <= newPos.y + 0.25f; y += 0.25f) {
			glm::vec2 pos = { x,y };

			bool collidable = pTilemap->CollidableAtPosition(pos);
			if (collidable) {
				TileData* tile = pTilemap->GetTileAtWorldPos(0, pos);

				ColQuad tileQuad;
				tileQuad.pos = { tile->colXPos, tile->colYPos };
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

	//std::cout << "Rotation: " << xVal << std::endl;

	//TIM_LOG_LOG("Player Forward: " << newForward.x << ", " << newForward.y);
	_pParentObject->GetTransform()->SetForward(newForward);
	//_pParentObject->GetTransform()->SetRotation(xVal);
}

void MovementComponent::OnStart()
{

}

void MovementComponent::OnUpdate()
{

}

void MovementComponent::OnEnd()
{

}
