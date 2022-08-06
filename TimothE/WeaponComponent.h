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

	void IncrementFrame();
	void ResetFrames();
	void SetToFrame(int val);

private:
	bool _swinging = false;

	glm::vec2 _originalPosition;

	class AnimatedSpritesheet* _pAnimSheet = nullptr;
	class SpriteComponent* _pSprite = nullptr;

	glm::vec2 _positionEachFrame[4];
	float _rotationEachFrame[4];
	int _currentFrame = 0;
	int _numberOfFrames = 4;
};

