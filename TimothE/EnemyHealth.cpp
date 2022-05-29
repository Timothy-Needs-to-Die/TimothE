#include "pch.h"
#include "EnemyHealth.h"
#include "AIController.h"
#include "OffensiveStructureObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "FarmScene.h"
#include "WaveManager.h"

EnemyHealth::EnemyHealth(GameObject* pOwner, int startingHealth)
	: Health(pOwner, startingHealth) {}

void EnemyHealth::OnDeath(GameObject* instigator)
{
	SceneManager::GetCurrentScene()->RemoveGameObject(_pParentObject);

	std::vector<GameObject*> towers = SceneManager::GetCurrentScene()->FindGameObjectsWithTag("TOWER");

	for (auto& obj : towers) {
		OffensiveStructureObject* offensive = dynamic_cast<OffensiveStructureObject*>(obj);
		if (offensive) {
			offensive->CheckTarget(_pParentObject);
		}
	}

	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());

	if (pFarmScene) {
		pFarmScene->GetWaveManager()->RemoveEnemyFromAliveList(dynamic_cast<Enemy*>(_pParentObject));
	}

	Health::OnDeath(instigator);
}

void EnemyHealth::OnDamage(GameObject* instigator)
{
	_pParentObject->GetComponent<AIController>()->AttackedBy(instigator);
	Health::OnDamage(instigator);
}
