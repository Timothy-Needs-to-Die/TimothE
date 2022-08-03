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
	class PlayerUIComponent* _pUI = nullptr;
	class BoxColliderComponent* _pCollider = nullptr;
	class FarmlandManager* _pFarmlandManager = nullptr;
	class WeaponObject* _pWeapon = nullptr;

	class TextComponent* _pInteractableUI = nullptr;
	class TextComponent* _pHealthUI = nullptr;

	GameObject* _pHealthObj = nullptr;

protected:
	virtual void UniqueLogic() override;
	void DisplayPlayerUI();
};

