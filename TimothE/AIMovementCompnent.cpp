#include "pch.h"
#include "AIMovementCompnent.h"

//constructor
AIMovementCompnent::AIMovementCompnent(GameObject* owner, AStar* pAStar)
	: MovementComponent(owner)
{
	SetType(Component::AIMovement_Type);

	_pAStar = pAStar;
	SetMovementSpeed(0.5f); //TODO: Get from config
	_pathToFollow = std::list<glm::vec2>();
}

//sets target destination of AI to move to
void AIMovementCompnent::SetDestination(glm::vec2 targetPos)
{
	//reset variables
	_pathToFollow.clear();
	_constantlyMove = false;
	_hasDestination = false;

	//sets map and finds path
	glm::vec2 tilePos = SceneManager::GetCurrentScene()->GetTileMap()->GetTileAtWorldPos(0, GetOwner()->GetTransform()->GetPosition())->pos;

	AStar* pLocal = _pAStar;

	glm::vec2& localDest = _destination;
	std::thread t([&tilePos, &targetPos, pLocal, this, &localDest]
		{
			std::vector<glm::vec2> tempPath;
			tempPath = pLocal->FindPath(tilePos, targetPos);

			AIMovementCompnent::FinishDestination();
			localDest = targetPos;

			//set path
			size_t size = tempPath.size();
			for (int i = 0; i < size; i++)
			{
				this->_pathToFollow.push_front(tempPath[i]);
			}

			//set next target
			this->_currentTarget = GetNextTarget();

			//clear paths
			tempPath.clear();
		});
	t.join();
}

void AIMovementCompnent::FinishDestination()
{
	_constantlyMove = true;
	_hasDestination = true;
}

void AIMovementCompnent::OnUpdate()
{

	MovementComponent::OnUpdate();

	GameObject* parent = GetOwner();

	//skip if no destination is found
	if (!_hasDestination) return;

	//distance to target
	float dist = glm::distance(parent->GetTransform()->GetPosition(), _currentTarget);

	//if player is in range of enemy set new target
	if (dist <= _tolerance)
	{
		_currentTarget = GetNextTarget();

	}
	//move towards player
	glm::vec2 direction = glm::normalize(_currentTarget - parent->GetTransform()->GetPosition());
	_desiredDirection = direction;


}

//get next target
glm::vec2 AIMovementCompnent::GetNextTarget()
{
	//if no path then stop movement and return
	if (_pathToFollow.size() == 0)
	{
		_constantlyMove = false;
		_hasDestination = false;

		return glm::vec2(0, 0);
	}


	//set target to move as the first path position
	_currentTarget = _pathToFollow.front();
	_pathToFollow.erase(_pathToFollow.begin());

	return _currentTarget; //return target
}
