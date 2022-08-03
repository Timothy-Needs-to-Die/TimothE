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

	struct Animation* _pArmDown = nullptr;
	struct Animation* _pArmLeft = nullptr;
	struct Animation* _pArmRight = nullptr;
	struct Animation* _pArmUp = nullptr;
	struct Animation* _pMoveDown = nullptr;
	struct Animation* _pMoveRight = nullptr;
	struct Animation* _pMoveUp = nullptr;
	struct Animation* _pMoveLeft = nullptr;
	struct Animation* _pArmAttack = nullptr;

	struct Animation* _pCurrentAnimation = nullptr;
	struct Animation* _pCurrentArmAnimation = nullptr;
};

