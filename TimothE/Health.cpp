#include "Health.h"
#include "SceneManager.h"
#include "Scene.h"
#include "AudioSource.h"


void Health::TakeDamage(int val, GameObject* instigator)
{
	if (_isDead) return;

	_currentHealth -= val;
	std::cout << "Current Health: " << _currentHealth << std::endl;
	if (_currentHealth <= 0) {
		OnDeath(instigator);
	}
	else {
		OnDamage(instigator);
		GetParent()->GetComponent<AudioSource>()->PlaySound("EnemyHit", 50, 60, 1, 1);
	}
}

void Health::OnDeath(GameObject* instigator)
{
	SceneManager::GetCurrentScene()->RemoveGameObject(this->GetParent());
}

void Health::OnHeal()
{
}

void Health::OnDamage(GameObject* instigator)
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
