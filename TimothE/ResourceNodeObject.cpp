#include "pch.h"
#include "ResourceNodeObject.h"
#include "ResourceNode.h"
#include "BoxColliderComponent.h"
#include "AudioSource.h"
#include "SpriteComponent.h"

#include "SpriteSheet.h"
#include "Sprite.h"

ResourceNodeObject::ResourceNodeObject(CoreResourceType type, std::string name /*= "Resource Node"*/, std::string tag /*= "RESOURCE_NODE"*/)
	: GameObject(name,tag)
{
	_pAudioSource = AddComponent(new AudioSource(this));
	_pResourceNode = AddComponent(new ResourceNode(this, type));
	_pCollider = AddComponent(new BoxColliderComponent(this));
	_pCollider->SetTrigger(true);

	SpriteComponent* sc = new SpriteComponent(this, 100);

	

	switch (type)
	{
	case CoreResourceType::Wood:
		sc->SetSprite(ResourceManager::GetSpriteSheet("small_wood")->GetSpriteAtIndex(0));
		break;
	case CoreResourceType::Stone:
		sc->SetSprite(ResourceManager::GetSpriteSheet("small_stone")->GetSpriteAtIndex(0));
		break;
	case CoreResourceType::Metal:
		sc->SetSprite(ResourceManager::GetSpriteSheet("small_metal")->GetSpriteAtIndex(0));
		break;
	case CoreResourceType::Gold:
		//sc->SetSprite(ResourceManager::GetSpriteSheet("small_wood")->GetSpriteAtIndex(0));
		break;
	case CoreResourceType::Coal:
		sc->SetSprite(ResourceManager::GetSpriteSheet("small_coal")->GetSpriteAtIndex(0));
		break;
	default:
		break;
	}

	AddComponent(sc);
}

void ResourceNodeObject::OnTriggerEnter(ColliderBase* other)
{

}
