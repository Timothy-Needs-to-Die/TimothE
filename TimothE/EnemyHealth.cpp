#include "EnemyHealth.h"
#include "AIController.h"

EnemyHealth::EnemyHealth(GameObject* pOwner, int startingHealth)
	: Health(pOwner, startingHealth) {}

void EnemyHealth::OnDeath(GameObject* instigator)
{
	SceneManager::GetCurrentScene()->RemoveGameObject(_pParentObject);
	Health::OnDeath(instigator);
}

void EnemyHealth::OnDamage(GameObject* instigator)
{
	_pParentObject->GetComponent<AIController>()->AttackedBy(instigator);
	Health::OnDamage(instigator);
}
