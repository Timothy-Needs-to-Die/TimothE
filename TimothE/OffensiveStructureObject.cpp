#include "OffensiveStructureObject.h"
#include "StructureFighter.h"

OffensiveStructureObject::OffensiveStructureObject(std::string name, std::string tag)
	: StructureObject(name, tag)
{
}

void OffensiveStructureObject::OnTriggerEnter(ColliderBase* other)
{
	if (other->GetParent()->GetTag() == "ENEMY") {
		_pEnemiesInRange.emplace_back(other->GetParent());
	}
}

void OffensiveStructureObject::OnTriggerExit(ColliderBase* other)
{
	if (other->GetParent()->GetTag() == "ENEMY") {
		GameObject* enemy = other->GetParent()
			;
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
		
	}

}
