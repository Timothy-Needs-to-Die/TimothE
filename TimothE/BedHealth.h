#pragma once
#include "Health.h"

class BedHealth : public Health
{
public:
	COMPONENT_STATIC_TYPE(Health_Type);

	BedHealth(GameObject* pOwner);

	virtual void OnDeath() override;
	virtual void OnDamage() override;
};

