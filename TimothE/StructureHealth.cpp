#include "StructureHealth.h"
#include "SceneManager.h"
#include "FarmScene.h"
#include "StructureObject.h"


StructureHealth::StructureHealth(GameObject* owner, int health)
	: Health(owner)
{
	SetMaxHealth(health);
}

void StructureHealth::OnDamage(GameObject* instigator)
{
}

void StructureHealth::OnDeath(GameObject* instigator)
{
	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());

	if (pFarmScene) {
		pFarmScene->RemoveStructure(dynamic_cast<StructureObject*>(_pParentObject));
	}
}

void StructureHealth::OnHeal()
{
}
