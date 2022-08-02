#include "pch.h"
#include "OffensiveStructureObject.h"
#include "StructureFighter.h"
#include "CircleColliderComponent.h"


OffensiveStructureObject::OffensiveStructureObject(std::string name, std::string tag)
	: StructureObject(name, tag)
{
	_pStructureFighter = AddComponent<StructureFighter>(new StructureFighter(this));
	_pCircleCollider = AddComponent<CircleColliderComponent>(new CircleColliderComponent(this));
	_pCircleCollider->SetTrigger(true);
	_pCircleCollider->SetScale(10.0f);
}

void OffensiveStructureObject::CheckTarget(GameObject* target)
{
	if (_pCurrentTarget == target) {
		_pCurrentTarget = _pEnemiesInRange[0];
	}
}

void OffensiveStructureObject::OnTriggerEnter(ColliderBase* other)
{
	if (other->GetOwner()->GetTag() == "ENEMY") {
		if (!other->GetOwner()->IsActive()) return;
		//TIM_LOG_LOG("Target in range");
		_pEnemiesInRange.emplace_back(other->GetOwner());
	}
}

void OffensiveStructureObject::OnTriggerExit(ColliderBase* other)
{
	if (other->GetOwner()->GetTag() == "ENEMY") {
		//TIM_LOG_LOG("Target not in range");
		GameObject* enemy = other->GetOwner();

		if (_pCurrentTarget == enemy) _pCurrentTarget = nullptr;

		if (enemy) {
			std::vector<GameObject*>::iterator it = std::find(_pEnemiesInRange.begin(), _pEnemiesInRange.end(), enemy);
			
			if (it != _pEnemiesInRange.end()) {
				_pEnemiesInRange.erase(it);
			}
		}
	}
}

void OffensiveStructureObject::UniqueLogic()
{
	if (_pCurrentTarget != nullptr) {
		if (!_pCurrentTarget->IsActive()) {
			_pCurrentTarget = nullptr;
		} else {
			_pStructureFighter->Attack(_pCurrentTarget);
			return;
		}
	}

	if (_pEnemiesInRange.size() == 0) return;
	
	glm::vec2 towerPos = GetTransform()->GetPosition();

	GameObject* closestEnemy = nullptr;
	float closestDistance = 1000000.0f;
	for (auto& obj : _pEnemiesInRange) {
		if(!obj->IsActive()) continue;
		float dist = glm::distance(towerPos, obj->GetTransform()->GetPosition());

		if (dist < closestDistance) {
			closestEnemy = obj;
			closestDistance = dist;
		}
	}

	if (closestEnemy != nullptr) {
		_pCurrentTarget = closestEnemy;
	}
}
