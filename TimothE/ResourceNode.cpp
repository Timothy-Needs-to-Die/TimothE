#include "pch.h"
#include "ResourceNode.h"
#include "PlayerResourceManager.h"
#include "ResourceManager.h"
#include "Time.h"
#include "AudioSource.h"

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
		if (_resourceType == CoreResourceType::Wood) {
			GetParent()->GetComponent<AudioSource>()->PlaySound("WoodChop", 20, 60, 0.3, 1);
		}
		if (_resourceType == CoreResourceType::Metal) {
			GetParent()->GetComponent<AudioSource>()->PlaySound("StoneMine", 20, 60, 0.3, 1);
		}
		if (_resourceType == CoreResourceType::Coal) {
			GetParent()->GetComponent<AudioSource>()->PlaySound("StoneMine", 20, 60, 0.3, 1);
		}
		if (_resourceType == CoreResourceType::Stone) {
			GetParent()->GetComponent<AudioSource>()->PlaySound("StoneMine", 20, 60, 0.3, 1);
		}
		
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



