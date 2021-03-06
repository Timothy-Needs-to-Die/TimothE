#pragma once
#include "Component.h"
#include "CoreResourceType.h"

class ResourceNode : public Component
{
public:
	COMPONENT_STATIC_TYPE(ResourceNode_Type);

	ResourceNode(GameObject* owner, CoreResourceType type);

	void Interact();
private:
	CoreResourceType _resourceType;

protected:
	float _timeBetweenHarvests = 1.5f;
	float _timer;

	// Inherited via Component
	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnEnd() override;

};

