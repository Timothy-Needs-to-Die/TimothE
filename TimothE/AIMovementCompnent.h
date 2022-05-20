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
	std::stack<glm::vec2> pathToFollow;
	glm::vec2 currentTarget;
	float tolerance = 0.05f;
	bool hasDestination;
	AStar* aStar;

	glm::vec2 GetNextTarget();

	glm::vec2 s = glm::vec2(1.0f, 1.0f);
	glm::vec2 e = glm::vec2(6.0f, 6.0f);
};

