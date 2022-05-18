#include "ResourceNode.h"
#include "PlayerResourceManager.h"
#include "ResourceManager.h"

ResourceNode::ResourceNode(GameObject* owner, CoreResourceType type)
	: Component(owner), _resourceType(type)
{
	SetType(Component::ResourceNodeType);
}

void ResourceNode::Interact()
{
	PlayerResourceManager::GetCoreResource(_resourceType)->GainResource(1);
}

void ResourceNode::OnStart()
{
}

void ResourceNode::OnUpdate()
{
}

void ResourceNode::OnEnd()
{
}



