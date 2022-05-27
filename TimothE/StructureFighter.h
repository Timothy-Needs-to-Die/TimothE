#pragma once
#include "Component.h"
class StructureFighter : public Component
{
public:
	COMPONENT_STATIC_TYPE(StructureFighter_Type);

	StructureFighter(GameObject* owner);

	void Attack(GameObject* pTarget);

	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;

private:
	float _attackRate = 2.5f;
	float _timeSinceLastAttack;
};

