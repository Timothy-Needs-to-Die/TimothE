#pragma once
#include "StructureObject.h"
#include <vector>
#include "Enemy.h"


class OffensiveStructureObject : public StructureObject
{
public:
	OffensiveStructureObject(std::string name = "Offensive Structure", std::string tag = "WALL");


	virtual void OnTriggerEnter(ColliderBase* other) override;
	virtual void OnTriggerExit(ColliderBase* other) override;
	virtual void UniqueLogic() override;

private:
	Enemy* _pCurrentTarget = nullptr;
	std::vector<GameObject*> _pEnemiesInRange;
	class StructureFighter* _pStructureFighter = nullptr;

};

