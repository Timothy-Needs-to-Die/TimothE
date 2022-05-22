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
	float distToPlayer = glm::distance({0.0,0.0}, player.GetTransform()->GetPosition()); //ai position

	if (distToPlayer < 0.0) //config.tolerance
	{
		currentTarget = player.GetParent();
	}

	if (currentTarget == nullptr)
	{
		FindTarget();
	}

	float distToTarget = glm::distance({ 0.0,0.0 }, currentTarget->GetTransform()->GetPosition());//ai pos

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
	std::vector<GameObject*> aTargets = SceneManager::GetCurrentScene()->FindGameObjectsWithTag(targetArr[0]);
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
