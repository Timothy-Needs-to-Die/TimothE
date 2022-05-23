#include "EnemyHealth.h"

EnemyHealth::EnemyHealth(GameObject* pOwner, int startingHealth)
	: Health(pOwner)
{
	SetMaxHealth(startingHealth);
}

void EnemyHealth::OnDeath()
{

}

void EnemyHealth::OnDamage()
{

}
