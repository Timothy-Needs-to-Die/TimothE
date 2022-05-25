#include "StructureHealth.h"
#include "SceneManager.h"
#include "FarmScene.h"
#include "StructureObject.h"


StructureHealth::StructureHealth(GameObject* owner, int health)
	: Health(owner)
{
	SetMaxHealth(health);
}

void StructureHealth::OnDamage()
{
	Health::OnDamage();
}

void StructureHealth::OnDeath()
{
	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());

	if (pFarmScene) {
		pFarmScene->RemoveStructure(dynamic_cast<StructureObject*>(_pParentObject));
	}
	
	Health::OnDeath();
}

void StructureHealth::OnHeal()
{
	Health::OnHeal();
}
