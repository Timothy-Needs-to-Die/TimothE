#pragma once
#include "Component.h"

class Health : public Component 
{

public:
	COMPONENT_STATIC_TYPE(Health_Type);

	Health(GameObject* pOwner, int startingHealth) : Component(pOwner) {
		SetType(Component::Types::Health_Type);
		SetMaxHealth(startingHealth);
	}

	void SetMaxHealth(int amount) {
		_maxHealth = amount;
		_currentHealth = _maxHealth;
	}

	void TakeDamage(int val, GameObject* instigator);

protected:
	int _currentHealth;
	int _maxHealth;
	bool _isDead = false;

	virtual void OnDeath(GameObject* instigator);
	virtual void OnHeal();
	virtual void OnDamage(GameObject* instigator);

	// Inherited via Component
	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnEnd() override;

};

