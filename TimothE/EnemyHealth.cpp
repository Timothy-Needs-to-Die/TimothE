#include "EnemyHealth.h"
#include "AIController.h"
#include "OffensiveStructureObject.h"
#include "SceneManager.h"
#include "Scene.h"

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

	Health::OnDeath(instigator);
}

void EnemyHealth::OnDamage(GameObject* instigator)
{
	_pParentObject->GetComponent<AIController>()->AttackedBy(instigator);
	Health::OnDamage(instigator);
}
