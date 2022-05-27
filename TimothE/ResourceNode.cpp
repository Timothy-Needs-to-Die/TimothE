#include "ResourceNode.h"
#include "PlayerResourceManager.h"
#include "ResourceManager.h"
#include "Time.h"

ResourceNode::ResourceNode(GameObject* owner, CoreResourceType type)
	: Component(owner), _resourceType(type)
{
	SetType(Component::ResourceNode_Type);
}

void ResourceNode::Interact()
{
	if (_timer > _timeBetweenHarvests) {
		_timer = 0.0f;
		PlayerResourceManager::GetCoreResource(_resourceType)->GainResource(1);
	}
}

void ResourceNode::OnStart()
{
}

void ResourceNode::OnUpdate()
{
	_timer += Time::GetDeltaTime();
}

void ResourceNode::OnEnd()
{
}



