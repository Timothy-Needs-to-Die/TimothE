#pragma once
#include "Health.h"
#include "GameObject.h"

class StructureHealth : public Health
{
public:
	COMPONENT_STATIC_TYPE(Health_Type);

	StructureHealth(GameObject* owner, int health);

private:
	virtual void OnDamage(GameObject* instigator) override;
	virtual void OnDeath(GameObject* instigator) override;
	virtual void OnHeal() override;

};

