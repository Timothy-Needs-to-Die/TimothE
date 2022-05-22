#pragma once
#include "StructureObject.h"
#include <vector>
#include "Enemy.h"


class OffensiveStructureObject : public StructureObject
{
public:
	OffensiveStructureObject(std::string name = "Offensive Structure", std::string tag = "TOWER");


	virtual void OnTriggerEnter(ColliderBase* other) override;
	virtual void OnTriggerExit(ColliderBase* other) override;
	virtual void UniqueLogic() override;

private:
	GameObject* _pCurrentTarget = nullptr;
	std::vector<GameObject*> _pEnemiesInRange;
	class StructureFighter* _pStructureFighter = nullptr;
	class CircleColliderComponent* _pCircleCollider = nullptr;

};

