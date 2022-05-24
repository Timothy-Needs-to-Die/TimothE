#include "EnemyHealth.h"
#include "AIController.h"

EnemyHealth::EnemyHealth(GameObject* pOwner, int startingHealth)
	: Health(pOwner)
{
	SetMaxHealth(startingHealth);
}

void EnemyHealth::OnDeath(GameObject* instigator)
{

}

void EnemyHealth::OnDamage(GameObject* instigator)
{
	_pParentObject->GetComponent<AIController>()->AttackedBy(instigator);
}
