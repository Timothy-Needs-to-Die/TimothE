#pragma once
#include "Health.h"
#include "GameObject.h"

class StructureHealth : public Health
{
public:
	COMPONENT_STATIC_TYPE(Health_Type);

	StructureHealth(GameObject* owner, int health);

private:
	virtual void OnDamage() override;
	virtual void OnDeath() override;
	virtual void OnHeal() override;

};

