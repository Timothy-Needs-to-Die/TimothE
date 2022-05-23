#pragma once

#include "MovementComponent.h"
#include "GameObject.h"
#include <stack>
#include "vector"
#include "AStar.h"
#include "SceneManager.h"
#include "Scene.h"
class AIMovementCompnent : public MovementComponent
{
public:


	AIMovementCompnent(GameObject* owner);

	void SetDestination(glm::vec2);
	virtual void OnUpdate() override;
private:
	std::list<glm::vec2> _mPathToFollow;
	glm::vec2 _mCurrentTarget;
	float _mTolerance = 0.05f;
	bool _mHasDestination;
	AStar* _pAStar;

	glm::vec2 GetNextTarget();
};

