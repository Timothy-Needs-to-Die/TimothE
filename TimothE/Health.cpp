#include "Health.h"
#include "SceneManager.h"
#include "Scene.h"


void Health::TakeDamage(int val)
{
	if (_isDead) return;

	_currentHealth -= val;
	std::cout << "Current Health: " << _currentHealth << std::endl;
	if (_currentHealth <= 0) {
		OnDeath();
	}
	else {
		OnDamage();
	}
}

void Health::OnDeath()
{
	SceneManager::GetCurrentScene()->RemoveGameObject(this->GetParent());
}

void Health::OnHeal()
{
}

void Health::OnDamage()
{
}

void Health::OnStart()
{
}

void Health::OnUpdate()
{
}

void Health::OnEnd()
{
}
