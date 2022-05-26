#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy(std::string name = "Enemy", std::string tag = "ENEMY");

	virtual void UniqueLogic() override;

private:
	class AIMovementCompnent* _pMover = nullptr;
	class AIController* _pController = nullptr;
	class EnemyHealth* _pHealth = nullptr;
	class Fighter* _pFighter = nullptr;
	class WeaponObject* _pWeapon = nullptr;
};

