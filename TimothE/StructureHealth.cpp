#include "StructureHealth.h"


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
}

void StructureHealth::OnHeal()
{
}
