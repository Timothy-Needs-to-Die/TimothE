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
	void SetDestination(glm::vec2);
	virtual void OnUpdate() override;
private:
	std::stack<glm::vec2> pathToFollow;
	glm::vec2 currentTarget;
	float tolerance;
	bool hasDestination;
	AStar* aStar;

	glm::vec2 GetNextTarget();
};

