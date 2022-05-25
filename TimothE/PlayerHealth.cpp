#include "PlayerHealth.h"
#include "SceneManager.h"

PlayerHealth::PlayerHealth(GameObject* pOwner, int health) : Health(pOwner)
{
	_maxHealth = health;
	_currentHealth = health;
}

void PlayerHealth::OnDeath()
{
	SceneManager::GetCurrentScene()->GameOver();
	Health::OnDeath();
}

void PlayerHealth::OnDamage()
{
	Health::OnDamage();
}