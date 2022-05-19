#pragma once
#include "Component.h"
#include "GameObject.h"
#include "WeaponConfig.h"
#include "Time.h"

class Fighter : public Component
{
public:
	COMPONENT_STATIC_TYPE(FighterType);

	Fighter(GameObject* pOwner) : Component(pOwner) {
		SetType(Component::Types::FighterType);
	}

	void SetWeaponConfig(const WeaponConfig& config) {
		_weaponConfig = config;
	}

	void Attack();


	// Inherited via Component
	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnEnd() override;

private:
	WeaponConfig _weaponConfig = WeaponConfig();
	
	float _timeSinceLastAttack = 0.0f;

	bool _canAttack = true;



};

