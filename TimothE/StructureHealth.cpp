#include "StructureHealth.h"
#include "SceneManager.h"
#include "FarmScene.h"
#include "StructureObject.h"
#include "AIController.h"


StructureHealth::StructureHealth(GameObject* owner, int health)
	: Health(owner, health) {}

void StructureHealth::OnDamage(GameObject* instigator)
{
}

void StructureHealth::OnDeath(GameObject* instigator)
{
	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());
	if (pFarmScene) {
		pFarmScene->RemoveStructure(dynamic_cast<StructureObject*>(_pParentObject));
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
}
