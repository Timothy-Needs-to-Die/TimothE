#include "AIController.h"
#include "Fighter.h"
#include "AIMovementCompnent.h"



AIController::AIController(GameObject* gameObject) : Component(gameObject)
{
	_mMoving = false;
	SetType(Types::AIControllerType);
	_pFighter = _pParentObject->AddComponent(new Fighter(_pParentObject));
}

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
	float distToPlayer = glm::distance(_pParentObject->GetTransform()->GetPosition(), _mPlayer.GetTransform()->GetPosition()); //ai position

	if (distToPlayer < 2.5) //config.tolerance
	{
		_pCurrentTarget = _mPlayer.GetParent();
	}

	if (_pCurrentTarget == nullptr)
	{
		FindTarget();
	}

	float distToTarget = glm::distance(_pParentObject->GetTransform()->GetPosition(), _pCurrentTarget->GetTransform()->GetPosition());//ai pos

	if (distToTarget < 0.3)//config.attackRange
	{
		_pFighter->Attack(_pParentObject);
		return;
	}
}

void AIController::OnEnd()
{

}

void AIController::SetTargetFromTag(string tagA, string tagB, string tagC)
{
	_mTargetArr[0] = tagA;
	_mTargetArr[1] = tagB;
	_mTargetArr[2] = tagC;
}

void AIController::FindTarget()
{
	GameObject* targetObj = nullptr;
	std::vector<GameObject*> aTargets = SceneManager::GetCurrentScene()->FindGameObjectsWithTag(_mTargetArr[0]);
	std::vector<GameObject*> bTargets = SceneManager::GetCurrentScene()->FindGameObjectsWithTag(_mTargetArr[1]);
	std::vector<GameObject*> cTargets = SceneManager::GetCurrentScene()->FindGameObjectsWithTag(_mTargetArr[2]);
	if (aTargets.size() != 0)
	{
		SetTarget( FindClosestTargetFromList(aTargets));
		return;
	}
	else if (bTargets.size() != 0)
	{
		SetTarget(FindClosestTargetFromList(bTargets));
		return;
	}
	else if (cTargets.size() != 0)
	{
		SetTarget(FindClosestTargetFromList(cTargets));
		return;
	}

	if (targetObj != nullptr)
	{
		return;
	}

	float distToPlayer = glm::distance(_pParentObject->GetTransform()->GetPosition(), _mPlayer.GetTransform()->GetPosition());
	float distToBed = glm::distance(_pParentObject->GetTransform()->GetPosition(), _mPlayer.GetTransform()->GetPosition()); //change player pos to bed pos
	if (distToPlayer < distToBed)
	{
		SetTarget(_mPlayer.GetParent());
	}
	else
	{
		SetTarget(_mPlayer.GetParent()); // change to bed
	}
}

void AIController::SetTarget(GameObject* target)
{
	_pCurrentTarget = target;
	_pParentObject->GetComponent<AIMovementCompnent>()->SetDestination(_pCurrentTarget->GetTransform()->GetPosition());
}

void AIController::AttackedBy(GameObject* instigator)
{
	if (instigator->GetTag() == "PLAYER")
	{	
		SetTarget(_mPlayer.GetParent());
		return;
	}
	if (instigator->GetTag() == "TOWER")
	{
		if (_pCurrentTarget == instigator)
		{
			return;
		}
	}
	if (_pCurrentTarget->GetTag() == "TOWER") return;
	SetTarget(instigator);
	return;
}

GameObject* AIController::FindClosestTargetFromList(std::vector<GameObject*> targets)
{
	GameObject* closestObj = nullptr;
	float closestDistance = FLT_MAX;
	for each (GameObject* go in targets)
	{
		float dist = glm::distance(this->GetParent()->GetTransform()->GetPosition(), go->GetTransform()->GetPosition());
		if (dist < closestDistance)
		{
			closestDistance = dist;
			closestObj = go;
		}
	}
	return closestObj;
}
