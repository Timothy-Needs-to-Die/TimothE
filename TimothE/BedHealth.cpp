#include "BedHealth.h"
#include "SceneManager.h"
#include "StructureHealth.h"

BedHealth::BedHealth(GameObject* pOwner, int health) : StructureHealth(pOwner, health)
{
}

void BedHealth::OnDeath()
{
	SceneManager::GetCurrentScene()->GameOver();
	StructureHealth::OnDeath();
}

void BedHealth::OnDamage()
{
	StructureHealth::OnDamage();
}
