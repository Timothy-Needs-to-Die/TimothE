#pragma once
#include "Health.h"

class PlayerHealth : public Health
{
public:
	COMPONENT_STATIC_TYPE(Health_Type);

	PlayerHealth(GameObject* pOwner, int health);

	virtual void OnDeath(GameObject* instigator) override;
protected:
	virtual void OnDamage(GameObject* instigator) override;
};
