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
	AddComponent(ResourceManager::GetTexture("lenna"));
}

void OffensiveStructureObject::OnTriggerEnter(ColliderBase* other)
{
	if (other->GetParent()->GetTag() == "PLAYER") {
		TIM_LOG_LOG("Target in range");
		_pEnemiesInRange.emplace_back(other->GetParent());
	}
}

void OffensiveStructureObject::OnTriggerExit(ColliderBase* other)
{
	if (other->GetParent()->GetTag() == "PLAYER") {
		TIM_LOG_LOG("Target not in range");

		GameObject* enemy = other->GetParent();

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
		_pStructureFighter->Attack(_pCurrentTarget);
		return;
	}

	if (_pEnemiesInRange.size() == 0) return;
	
	glm::vec2 towerPos = GetTransform()->GetPosition();

	GameObject* closestEnemy = nullptr;
	float closestDistance = 1000000.0f;
	for (auto& obj : _pEnemiesInRange) {
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
