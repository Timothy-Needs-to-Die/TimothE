#pragma once
#include "Component.h"

class WeaponComponent : public Component
{
public:
	COMPONENT_STATIC_TYPE(Weapon_Type)

	WeaponComponent(GameObject* object);

	// Inherited via Component
	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnEnd() override;

	void StartAttack();
	void EndAttack();

	void SetWeaponLevel(int level) { _currentLevel = level; }
	int GetWeaponLevel() const { return _currentLevel; }

private:
	int _currentLevel = 0;
	int _amountOfLevels = 6;

	class AnimatedSpritesheet* _pAnimSheet = nullptr;
	class SpriteComponent* _pSprite = nullptr;

};

