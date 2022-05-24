#include "BedHealth.h"
#include "SceneManager.h"

BedHealth::BedHealth(GameObject* pOwner) : Health(pOwner)
{
}

void BedHealth::OnDeath()
{
	SceneManager::GetCurrentScene()->GameOver();
	Health::OnDeath();
}

void BedHealth::OnDamage()
{
	Health::OnDamage();
}
