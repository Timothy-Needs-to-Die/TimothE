#pragma once
#include "GameObject.h"

class SceneTransitionObject : public GameObject
{
public:
	SceneTransitionObject(std::string destination, std::string name = "SceneTransitionObject", std::string tag = "TRANSITION_POINT");
	
	void OnTriggerEnter(ColliderBase* other) override;

private:
	//The box collider will intersect with the player to move them from map A to B
	class BoxColliderComponent* _pBoxCollider = nullptr;

	//The destination string is used to tell what scene this transition object will take the player
	//and where on that map the player will move to
	std::string _destination;
};

