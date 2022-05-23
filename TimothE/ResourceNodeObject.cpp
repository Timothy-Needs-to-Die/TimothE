#include "ResourceNodeObject.h"
#include "ResourceNode.h"
#include "BoxColliderComponent.h"

ResourceNodeObject::ResourceNodeObject(CoreResourceType type, std::string name /*= "Resource Node"*/, std::string tag /*= "RESOURCE_NODE"*/)
	: GameObject(name,tag)
{
	_pResourceNode = AddComponent(new ResourceNode(this, type));
	_pCollider = AddComponent(new BoxColliderComponent(this));
	_pCollider->SetTrigger(true);

	switch (type)
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
	case Coal:
		AddComponent(ResourceManager::GetTexture("small_coal"));
		break;
	default:
		break;
	}

	GetTransform()->SetScale({ 0.25f, 0.25f });
}

void ResourceNodeObject::OnTriggerEnter(ColliderBase* other)
{

}
