#include "pch.h"
#include "StructureHealth.h"
#include "SceneManager.h"
#include "FarmScene.h"
#include "StructureObject.h"
#include "AIController.h"


StructureHealth::StructureHealth(GameObject* owner, int health)
	: Health(owner, health) {}

void StructureHealth::OnDamage(GameObject* instigator)
{
	Health::OnDamage(instigator);
}

void StructureHealth::OnDeath(GameObject* instigator)
{
	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());
	if (pFarmScene) {
		pFarmScene->RemoveStructure(dynamic_cast<StructureObject*>(_pOwner));
	}

	AIController* pAi = instigator->GetComponent<AIController>();
	if (pAi) {
		std::vector<AIController*> ai = SceneManager::GetCurrentScene()->FindObjectsOfType<AIController>();
		for (auto& a : ai) {
			a->CheckTarget(instigator);
		}
	}
}

void StructureHealth::OnHeal()
{
	Health::OnHeal();
}
