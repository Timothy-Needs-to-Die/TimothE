#include "StructureHealth.h"


StructureHealth::StructureHealth(GameObject* owner, int health)
	: Health(owner)
{
	SetMaxHealth(health);
}

void StructureHealth::OnDamage()
{
}

void StructureHealth::OnDeath()
{
}

void StructureHealth::OnHeal()
{
}
