#pragma once
#include "Health.h"

class EnemyHealth : public Health
{
public:
	COMPONENT_STATIC_TYPE(Health_Type);

	EnemyHealth(GameObject* pOwner, int startingHealth);

	virtual void OnDeath() override;
	virtual void OnDamage() override;
	
};

