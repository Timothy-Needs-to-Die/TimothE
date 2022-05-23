#include "AIMovementCompnent.h"

//constructor
AIMovementCompnent::AIMovementCompnent(GameObject* owner)
	: MovementComponent(owner)
{
	_pAStar = SceneManager::GetCurrentScene()->FindObjectOfType<AStar>();
	//_mAStar = new AStar();
	SetMovementSpeed(0.5f); //TODO: Get from config
}

//sets target destination of AI to move to
void AIMovementCompnent::SetDestination(glm::vec2 targetPos)
{
	//reset variables
	_mPathToFollow.clear();
	_constantlyMove = true;
	_mHasDestination = true;

	//sets map and finds path
	_pAStar->SetMap(SceneManager::GetCurrentScene()->GetTileMap());
	std::vector<glm::vec2> tempPath = _pAStar->FindPath(GetParent()->GetTransform()->GetPosition(), targetPos);

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
	_mCurrentTarget = _mPathToFollow.back();
	_mPathToFollow.erase(_mPathToFollow.begin());

	return _mCurrentTarget; //return target
}
