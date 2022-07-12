#pragma once
#include "Component.h"

class WeaponComponent : public Component
{
public:
	COMPONENT_STATIC_TYPE(Weapon_Type)

	WeaponComponent(GameObject* object);

	// Inherited via Component
	virtual void OnUpdate() override;

	void StartAttack();
	void EndAttack();

	void SetWeaponLevel(int level) { _currentLevel = level; }
	int GetWeaponLevel() const { return _currentLevel; }

private:
	int _currentLevel = 0;
	int _amountOfLevels = 6;

	bool _swinging = false;

	glm::vec2 _originalPosition;

	class AnimatedSpritesheet* _pAnimSheet = nullptr;
	class SpriteComponent* _pSprite = nullptr;

};

