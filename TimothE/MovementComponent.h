#pragma once
#include "Component.h"


enum class Direction {
	STATIONARY,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class MovementComponent : public Component
{

public:
	MovementComponent(GameObject* gameObject) : Component(gameObject) 
	{
		_direction = Direction::STATIONARY;
		_moving = false;
		SetType(Types::Movement);
	}

	COMPONENT_STATIC_TYPE(Movement);
	

	void Move(glm::vec2 moveVec);

	void CollisionCheck(glm::vec2& newPos);

	void DecideDirection(glm::vec2& moveVec);

	void SetMovementSpeed(const float speed) {
		_movementSpeed = speed;
	}
	float GetMovementSpeed() const { return _movementSpeed; }

	void SetMoveDirection(glm::vec2 dir) { _desiredDirection = dir; }
	glm::vec2 GetMoveDirection() const { return _desiredDirection; }

	bool IsMoving() const { return _moving; }

	Direction GetDirection() const { return _direction; }

	void SetAllowCollisions(bool val) { _allowCollisions = val; }

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	void SetConstantlyMove(bool val) { _constantlyMove = val; }


private:
	float _movementSpeed = 3.0f;
	bool _moving;
	bool _allowCollisions = true;

	

	Direction _direction;

protected:
	bool _constantlyMove;
	glm::vec2 _desiredDirection;

};

