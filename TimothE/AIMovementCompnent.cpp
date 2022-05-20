#include "AIMovementCompnent.h"

void AIMovementCompnent::SetDestination(glm::vec2 targetPos)
{
	std::vector<Node*> tempPath = aStar->GetPathOfNodes();
	for (int i = 0; i < tempPath.size(); i++)
	{
		pathToFollow.push(tempPath.at(i)->pos);
	}
	tempPath.clear();
}

void AIMovementCompnent::OnUpdate()
{
	MovementComponent::OnUpdate();

	GameObject* parent = GetParent();
	
	if (hasDestination) return;

	float dist = glm::distance(parent->GetTransform()->GetPosition(), currentTarget);
	if (dist < tolerance)
	{
		currentTarget = GetNextTarget();
	}
}

glm::vec2 AIMovementCompnent::GetNextTarget()
{
	if (pathToFollow.size() == 0)
	{
		hasDestination = false;
		return glm::vec2(0, 0);
	}

	currentTarget = pathToFollow.top();
	pathToFollow.pop();
}
