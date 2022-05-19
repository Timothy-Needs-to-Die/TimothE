#pragma once
#include "GameObject.h"
#include "ResourceNode.h"
#include "PlayerResourceManager.h"

class ResourceNodeObject : public GameObject
{
public:
	ResourceNodeObject(CoreResourceType type, std::string name = "Resource Node", std::string tag = "RESOURCE_NODE");


	virtual void OnTriggerEnter(ColliderBase* other) override;
private:
	class ResourceNode* _pResourceNode;
	class BoxColliderComponent* _pCollider;

	

protected:

};

