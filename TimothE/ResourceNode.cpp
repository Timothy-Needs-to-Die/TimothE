#include "ResourceNode.h"
#include "PlayerResourceManager.h"

ResourceNode::ResourceNode(std::string name /*= "Resource Node"*/, CoreResourceType type)
	: GameObject(name, "RESOURCE_NODE"), _resourceType(type)
{
	_pCollider = AddComponent(new BoxColliderComponent(this));

	switch (_resourceType)
	{
	case Wood:
		AddComponent(ResourceManager::GetTexture("small_wood"));
		break;
	case Stone:
		AddComponent(ResourceManager::GetTexture("small_stone"));
		break;
	case Metal:
		AddComponent(ResourceManager::GetTexture("small_metal"));
		break;
	case Gold:

		break;
	default:
		break;
	}

	GetTransform()->SetScale({ 0.25f, 0.25f });

}

void ResourceNode::Interact()
{
	PlayerResourceManager::GetCoreResource(_resourceType)->GainResource(1);
}



