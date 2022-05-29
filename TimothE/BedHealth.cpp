#include "pch.h"
#include "Bed.h"

#include "BedHealth.h"
#include "SceneManager.h"
#include "StructureHealth.h"

BedHealth::BedHealth(GameObject* pOwner, int health) : StructureHealth(pOwner, health)
{
}

void BedHealth::OnDeath(GameObject* instigator)
{
	SceneManager::GetCurrentScene()->GameOver();
	StructureHealth::OnDeath(instigator);
}

void BedHealth::OnDamage(GameObject* instigator)
{
	StructureHealth::OnDamage(instigator);
}
