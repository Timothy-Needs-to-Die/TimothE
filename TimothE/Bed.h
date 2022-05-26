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
	class BoxColliderComponent* _pBoxCollider;
	class Texture2D* _pTexture;
};