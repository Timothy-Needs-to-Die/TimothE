#include "PlayerHealth.h"
#include "SceneManager.h"

PlayerHealth::PlayerHealth(GameObject* pOwner, int health) : Health(pOwner, health)
{
	_maxHealth = health;
	_currentHealth = health;
}

void PlayerHealth::OnDeath(GameObject* instigator)
{
	SceneManager::GetCurrentScene()->GameOver();
	Health::OnDeath(instigator);
}

void PlayerHealth::OnDamage(GameObject* instigator)
{
	Health::OnDamage(instigator);
}