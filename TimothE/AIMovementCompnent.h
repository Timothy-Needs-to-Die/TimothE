#pragma once

#include "MovementComponent.h"
#include "GameObject.h"
#include <stack>
#include "vector"
#include "AStar.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ThreadMaster.h"
#include "ThreadWorker.h"

class AIMovementCompnent : public MovementComponent
{
public:
	COMPONENT_STATIC_TYPE(AIMovement_Type);

	AIMovementCompnent(GameObject* owner, AStar* pAStar);

	void SetDestination(glm::vec2);
	void FinishDestination();
	
	glm::vec2 GetDestination() const { return _destination;  }

	virtual void OnUpdate() override;
private:

	glm::vec2 _destination;
	std::list<glm::vec2> _pathToFollow;
	glm::vec2 _currentTarget;
	float _tolerance = 0.05f;
	bool _hasDestination;
	AStar* _pAStar;

	glm::vec2 GetNextTarget();
};

