#include "AIMovementCompnent.h"

AIMovementCompnent::AIMovementCompnent(GameObject* owner)
	: MovementComponent(owner)
{

	aStar = new AStar();
	aStar->SetMap(SceneManager::GetCurrentScene()->GetTileMap());
	SetMovementSpeed(0.5f); //TODO: Get from config
}

void AIMovementCompnent::SetDestination(glm::vec2 targetPos)
{
	_constantlyMove = true;
	hasDestination = true;
	std::vector<glm::vec2> tempPath = aStar->FindPath(GetParent()->GetTransform()->GetPosition(),targetPos);

	int size = tempPath.size();
	for (int i = 0; i < size; i++)
	{
		pathToFollow.push(tempPath[i]);
		//tempPath.pop_front();
		//pathToFollow.pop();
	}

	currentTarget = GetNextTarget();
	tempPath.clear();
}

void AIMovementCompnent::OnUpdate()
{
	MovementComponent::OnUpdate();

	GameObject* parent = GetParent();
	
	if (!hasDestination) return;

	float dist = glm::distance(parent->GetTransform()->GetPosition(), currentTarget);
	if (dist <= tolerance)
	{
		currentTarget = GetNextTarget();

	}
	glm::vec2 direction = glm::normalize(currentTarget - parent->GetTransform()->GetPosition());
	_desiredDirection = direction;
}

glm::vec2 AIMovementCompnent::GetNextTarget()
{
	if (pathToFollow.size() == 0)
	{
		_constantlyMove = false;
		hasDestination = false;

		//SetDestination(glm::vec2{ 0.0f,0.0f });

		return glm::vec2(0, 0);
	}

	currentTarget = pathToFollow.top();
	pathToFollow.pop();

	return currentTarget;
}
