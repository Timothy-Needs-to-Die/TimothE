#pragma once
#include "GameObject.h"
//#include "Health.h"

class Bed : public GameObject
{
public:
	Bed();
	~Bed();
	void UniqueLogic() override;
	void OnTriggerEnter(ColliderBase* other) override;
	void OnTriggerExit(ColliderBase* other) override;
	bool canSleepThroughNight = false;
	bool isEPressed = false;


private:
	class BedHealth* _pHealth;
	class BoxColliderComponent* _pBoxCollider;
	Texture2D* _pTexture;

	bool _isInRange = false;
	bool _isKeyUP = true;
	//class Health* playerhealth = nullptr;
};