#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name = "Player", std::string tag = "PLAYER");

private:
	class Fighter* _pFighter = nullptr;
	class PlayerHealth* _pHealth = nullptr;
	class PlayerInputComponent* _pInput = nullptr;
	class BoxColliderComponent* _pCollider = nullptr;

protected:
	virtual void UniqueLogic() override;

};

