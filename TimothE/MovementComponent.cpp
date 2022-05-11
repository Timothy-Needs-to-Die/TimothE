#include "MovementComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "TileMap.h"
#include "Time.h"
#include "SceneManager.h"


void MovementComponent::Move(glm::vec2 moveVec)
{
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
				std::cout << "Collidable" << std::endl;

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

			//if (tile->collidable) {
			//	if (Physics::Intersects(playerQuad, tileQuad)) {

			//		float dx1 = tileQuad.pos.x - playerQuad.max.x;
			//		float dx2 = tileQuad.max.x - playerQuad.pos.x;
			//		float dy1 = tileQuad.pos.y - playerQuad.max.y;
			//		float dy2 = tileQuad.max.y - playerQuad.pos.y;

			//		float dx = (abs(dx1) < abs(dx2)) ? dx1 : dx2;
			//		float dy = (abs(dy1) < abs(dy2)) ? dy1 : dy2;

			//		if (abs(dx) <= abs(dy)) {
			//			newPos.x += dx;
			//		}
			//		else if (abs(dy) <= abs(dx)) {
			//			newPos.y += dy;
			//		}
			//	}
			//}
		}
	}
}

void MovementComponent::DecideDirection(glm::vec2& moveVec)
{
	//If the x value is greater than or equal to y value
	if (moveVec.x >= moveVec.y) {
		//We are moving left or right. Decide based on if the x component is greater than 0
		_direction = moveVec.x > 0.0f ? Direction::RIGHT : Direction::LEFT;
	}
	else {
		//We are moving up or down. Decide based on if the y component is greater than 0
		_direction = moveVec.y > 0.0f ? Direction::UP : Direction::DOWN;
	}
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
