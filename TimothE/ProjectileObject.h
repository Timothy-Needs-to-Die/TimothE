#pragma once
#include "GameObject.h"
class ProjectileObject : public GameObject
{
public:
	ProjectileObject(glm::vec2 spawnPosition, glm::vec2 direction, std::string name = "PROJECTILE", std::string tag = "PROJECTILE");

	virtual void UniqueLogic() override;

	virtual void OnTriggerEnter(ColliderBase* other) override;

private:

	class MovementComponent* _pMover = nullptr;
	class BoxColliderComponent* _pBoxCollider = nullptr;
	


};

