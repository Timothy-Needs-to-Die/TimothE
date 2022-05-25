#pragma once
#include "StructureHealth.h"

class BedHealth : public StructureHealth
{
public:
	COMPONENT_STATIC_TYPE(Health_Type);

	BedHealth(GameObject* pOwner, int health);

protected:
	virtual void OnDeath() override;
	virtual void OnDamage() override;
};

