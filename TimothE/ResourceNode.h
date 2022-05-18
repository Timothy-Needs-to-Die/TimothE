#pragma once
#include "GameObject.h"
#include "CoreResourceType.h"
class ResourceNode : public GameObject
{
public:
	ResourceNode(std::string name = "Resource Node", CoreResourceType type = Wood);

	void Interact();
private:
	BoxColliderComponent* _pCollider;


	CoreResourceType _resourceType;

protected:

};

