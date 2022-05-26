#include "AIMovementCompnent.h"

//constructor
AIMovementCompnent::AIMovementCompnent(GameObject* owner, AStar* pAStar)
	: MovementComponent(owner)
{
	SetType(Component::AIMovement_Type);

	_pAStar = pAStar;
	//_mAStar = new AStar();
	SetMovementSpeed(0.5f); //TODO: Get from config
	_mPathToFollow = std::list<glm::vec2>();
}

//sets target destination of AI to move to
void AIMovementCompnent::SetDestination(glm::vec2 targetPos)
{
	//reset variables
	_mPathToFollow.clear();
	_constantlyMove = true;
	_mHasDestination = true;

	//sets map and finds path
	
	glm::vec2 tilePos = SceneManager::GetCurrentScene()->GetTileMap()->GetTileAtWorldPos(0, GetParent()->GetTransform()->GetPosition())->pos;
	std::vector<glm::vec2> tempPath = _pAStar->FindPath(tilePos, targetPos);

	_destination = targetPos;

	//set path
	int size = tempPath.size();
	for (int i = 0; i < size; i++)
	{
   		_mPathToFollow.push_front(tempPath[i]);
	}

	//set next target
	_mCurrentTarget = GetNextTarget();

	//clear paths
	_pAStar->processedPath.clear();
	tempPath.clear();

}

void AIMovementCompnent::OnUpdate()
{

	MovementComponent::OnUpdate();

	GameObject* parent = GetParent();

	//skip if no destination is found
	if (!_mHasDestination) return;

	//distance to target
	float dist = glm::distance(parent->GetTransform()->GetPosition(), _mCurrentTarget);

	//if player is in range of enemy set new target
	if (dist <= _mTolerance)
	{
		_mCurrentTarget = GetNextTarget();

	}
	//move towards player
	glm::vec2 direction = glm::normalize(_mCurrentTarget - parent->GetTransform()->GetPosition());
	_desiredDirection = direction;


}

//get next target
glm::vec2 AIMovementCompnent::GetNextTarget()
{
	//if no path then stop movement and return
	if (_mPathToFollow.size() == 0)
	{
		_constantlyMove = false;
		_mHasDestination = false;

		return glm::vec2(0, 0);
	}


	//set target to move as the first path position
	_mCurrentTarget = _mPathToFollow.front();
	_mPathToFollow.erase(_mPathToFollow.begin());

	return _mCurrentTarget; //return target
}
