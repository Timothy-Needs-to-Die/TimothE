#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "TileMap.h"
#include "Time.h"
#include "SceneManager.h"
#include "Player.h"



class AIController : public Component
{

public:
	AIController(GameObject* gameObject) : Component(gameObject) 
	{
		_moving = false;
		SetType(Types::AIControllerType);
	}

	COMPONENT_STATIC_TYPE(AIControllerType);
	

	void Move(glm::vec2 moveVec);

	void CollisionCheck(glm::vec2& newPos);

	void DecideDirection(glm::vec2& moveVec);

	void SetMovementSpeed(const float speed) {
		_movementSpeed = speed;
	}
	float GetMovementSpeed() const { return _movementSpeed; }

	bool IsMoving() const { return _moving; }


	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	void SetTargetFromTag(string tagA, string tagB, string tagC);
	void FindTarget();
	void AttackedBy(GameObject object);

private:
	float _movementSpeed = 3.0f;
	bool _moving = true;

	class Fighter* _pFighter = nullptr;
	GameObject* currentTarget = nullptr;
	string targetArr[3];
	Player player;

	GameObject* FindClosestTargetFromList(std::vector<GameObject*> targets);
};

