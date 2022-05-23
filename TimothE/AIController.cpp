#include "AIController.h"




void AIController::Move(glm::vec2 moveToVec)
{
	Transform* transform = _pParentObject->GetTransform();
	transform->SetPosition(moveToVec);
}



void AIController::OnStart()
{

}

void AIController::OnUpdate()
{
	float distToPlayer = glm::distance({0.0,0.0}, _mPlayer.GetTransform()->GetPosition()); //ai position

	if (distToPlayer < 0.0) //config.tolerance
	{
		_pCurrentTarget = _mPlayer.GetParent();
	}

	if (_pCurrentTarget == nullptr)
	{
		FindTarget();
	}

	float distToTarget = glm::distance({ 0.0,0.0 }, _pCurrentTarget->GetTransform()->GetPosition());//ai pos

	if (distToTarget < 0)//config.attackRange
	{
		//_pFighter->Attack(); no function
	}
}

void AIController::OnEnd()
{

}

void AIController::SetTargetFromTag(string tagA, string tagB, string tagC)
{
}

void AIController::FindTarget()
{
	GameObject* targetObj = nullptr;
	std::vector<GameObject*> aTargets = SceneManager::GetCurrentScene()->FindGameObjectsWithTag(_mTargetArr[0]);
	if (aTargets.size() != 0)
	{
		FindClosestTargetFromList(aTargets); //use return to set target
	}
}

void AIController::AttackedBy(GameObject object)
{
}

GameObject* AIController::FindClosestTargetFromList(std::vector<GameObject*> targets)
{
	return 0;
}
