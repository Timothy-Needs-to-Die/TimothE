#include "AIController.h"
#include "Fighter.h"
#include "AIMovementCompnent.h"



AIController::AIController(GameObject* gameObject) : Component(gameObject)
{
	SetType(Types::AIControllerType);
	_pFighter = _pParentObject->AddComponent(new Fighter(_pParentObject));
	_pPlayer = dynamic_cast<Player*>(SceneManager::GetCurrentScene()->GetGameObjectByName("Player"));

	_pPlayerTransform = _pPlayer->GetTransform();
	_pOwnerTransform = _pParentObject->GetTransform();
	_pMover = _pParentObject->GetComponent<AIMovementCompnent>();
}

void AIController::OnStart()
{

}

void AIController::OnUpdate()
{
	if (_pCurrentTarget)
	{
		if (glm::distance(_pMover->GetDestination(), _pTargetTransform->GetPosition()) > 1.0f) {
			_pMover->SetDestination(_pTargetTransform->GetPosition());
		}
	}

	float distToPlayer = glm::distance(_pOwnerTransform->GetPosition(), _pPlayerTransform->GetPosition()); //ai position

	if (distToPlayer < 2.5) //config.tolerance
	{
		_pCurrentTarget = _pPlayer;
	}

	if (_pCurrentTarget == nullptr)
	{
		TIM_LOG_LOG("Finding Target");
		FindTarget();
	}

	float distToTarget = glm::distance(_pOwnerTransform->GetPosition(), _pCurrentTarget->GetTransform()->GetPosition());//ai pos

	if (distToTarget < 0.3) //config.attackRange
	{
		_pFighter->Attack(_pParentObject);
		return;
	}
}

void AIController::OnEnd()
{

}

void AIController::SetTargetTags(std::string tagA, std::string tagB, std::string tagC)
{
	_mTargetArr[0] = tagA;
	_mTargetArr[1] = tagB;
	_mTargetArr[2] = tagC;
}

void AIController::FindTarget()
{
	std::vector<GameObject*> aTargets = SceneManager::GetCurrentScene()->FindGameObjectsWithTag(_mTargetArr[0]);
	if (aTargets.size() != 0)
	{
		SetTarget( FindClosestTargetFromList(aTargets));
		return;
	}


	std::vector<GameObject*> bTargets = SceneManager::GetCurrentScene()->FindGameObjectsWithTag(_mTargetArr[1]);
	if (bTargets.size() != 0)
	{
		SetTarget(FindClosestTargetFromList(bTargets));
		return;
	}

	std::vector<GameObject*> cTargets = SceneManager::GetCurrentScene()->FindGameObjectsWithTag(_mTargetArr[2]);
	if (cTargets.size() != 0)
	{
		SetTarget(FindClosestTargetFromList(cTargets));
		return;
	}

	float distToPlayer = glm::distance(_pOwnerTransform->GetPosition(), _pPlayerTransform->GetPosition());
	float distToBed = 1000.0f;  //TODO: change to getting distance to bed object
	if (distToPlayer < distToBed)
	{
		SetTarget(_pPlayer);
	}
	else
	{
		//TODO: Set Target Bed
	}
}

void AIController::SetTarget(GameObject* target)
{
	_pCurrentTarget = target;
	_pTargetTransform = _pCurrentTarget->GetTransform();

	float mag = glm::length(_pTargetTransform->GetPosition() + _pOwnerTransform->GetPosition());
	if (mag > 1.0f) {
		_pMover->SetDestination(_pTargetTransform->GetPosition());
	}
}

void AIController::AttackedBy(GameObject* instigator)
{
	if (instigator->GetTag() == "PLAYER")
	{	
		SetTarget(_pPlayer);
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
		float dist = glm::distance(_pOwnerTransform->GetPosition(), go->GetTransform()->GetPosition());
		if (dist < closestDistance)
		{
			closestDistance = dist;
			closestObj = go;
		}
	}
	return closestObj;
}
