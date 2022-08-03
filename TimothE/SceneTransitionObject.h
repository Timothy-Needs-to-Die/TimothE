#pragma once
#include "GameObject.h"

class SceneTransitionObject : public GameObject
{
public:

	SceneTransitionObject(std::string destination, std::string name = "SceneTransitionObject", std::string tag = "TRANSITION_POINT");

	
	void OnTriggerEnter(ColliderBase* other) override;

private:
	class BoxColliderComponent* _pBoxCollider = nullptr;

	std::string _destination;
	bool _transitioning = false;
};

