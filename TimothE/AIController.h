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
	AIController(GameObject* gameObject);

	COMPONENT_STATIC_TYPE(AIControllerType);


	void Move(glm::vec2 moveVec);

	void CollisionCheck(glm::vec2& newPos);

	void DecideDirection(glm::vec2& moveVec);

	void SetMovementSpeed(const float speed) {
		_mMovementSpeed = speed;
	}
	float GetMovementSpeed() const { return _mMovementSpeed; }

	bool IsMoving() const { return _mMoving; }


	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	void SetTargetFromTag(string tagA, string tagB, string tagC);
	void FindTarget();
	void SetTarget(GameObject* target);
	void AttackedBy(GameObject* instigator);

private:
	float _mMovementSpeed = 3.0f;
	bool _mMoving = true;

	class Fighter* _pFighter = nullptr;
	GameObject* _pCurrentTarget = nullptr;
	string _mTargetArr[3];
	Player* _mPlayer;
	GameObject* FindClosestTargetFromList(std::vector<GameObject*> targets);
};

