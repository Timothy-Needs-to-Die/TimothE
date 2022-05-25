#pragma once
#include "GameObject.h"

class Bed : public GameObject
{
public:
	Bed();
	~Bed();

	void OnTriggerEnter(ColliderBase* other) override;

private:
	class BedHealth* _pHealth;
	BoxColliderComponent* _pBoxCollider;
	Texture2D* _pTexture;
};