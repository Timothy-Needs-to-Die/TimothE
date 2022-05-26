#pragma once
#include "GameObject.h"
class WeaponObject : public GameObject
{
public:
	WeaponObject(std::string name = "Weapon", std::string tag = "WEAPON");

	virtual void UniqueLogic() override;

private:
	class WeaponComponent* _pWeaponComp = nullptr;
};

