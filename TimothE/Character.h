#pragma once
#include "GameObject.h"


class Character : public GameObject
{
public:
	Character(std::string texutre, std::string name = "New Character", std::string tag = "UNTAGGED");

private:
	

protected:
	virtual void UniqueLogic() override;

	
	class MovementComponent* _pMovement = nullptr;
	class AnimatedSpritesheet* _pAnimSheet;
	class SpriteComponent* _pSc = nullptr;
	class AudioSource* _pAudioSource = nullptr;
};

