#pragma once
#include "GameObject.h"


class Character : public GameObject
{
public:
	Character(std::string texutre, std::string name = "New Character", std::string tag = "UNTAGGED");

	void SetAttacking(bool val);


	~Character();

private:

protected:
	virtual void UniqueLogic() override;

	bool _isAttacking = false;
	
	class MovementComponent* _pMovement = nullptr;
	class AnimatedSpritesheet* _pAnimSheet;
	class SpriteComponent* _pSc = nullptr;
	class SpriteComponent* _pArmSc = nullptr;

	class AudioSource* _pAudioSource = nullptr;

	struct Animation* _pArmDown;
	struct Animation* _pArmLeft;
	struct Animation* _pArmRight;
	struct Animation* _pArmUp;
	struct Animation* _pMoveDown;
	struct Animation* _pMoveRight;
	struct Animation* _pMoveUp;
	struct Animation* _pMoveLeft;
	struct Animation* _pArmAttack;

	struct Animation* _pCurrentAnimation;
	struct Animation* _pCurrentArmAnimation;
};

