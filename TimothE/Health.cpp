#include "pch.h"
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
	if (GetParent()->GetComponent<AudioSource>() != NULL)
	{
		GetParent()->GetComponent<AudioSource>()->PlaySound("EnemyHit", 0.5, 0.5, 1, 1);
	}
	
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
