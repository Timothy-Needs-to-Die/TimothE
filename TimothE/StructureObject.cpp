#include "pch.h"
#include "StructureObject.h"
#include "StructureHealth.h"

#include "SpriteComponent.h"
#include "SpriteSheet.h"
#include "Sprite.h"

StructureObject::StructureObject(std::string name, std::string tag)
	:  GameObject(name, tag)
{
	SpriteComponent* sc = AddComponent(new SpriteComponent(this, 100));

	if (tag == "WALL") {
		sc->SetSprite(ResourceManager::GetSpriteSheet("wall")->GetSpriteAtIndex(0));
	}
	else if (tag == "TOWER") {
		sc->SetSprite(ResourceManager::GetSpriteSheet("tower")->GetSpriteAtIndex(0));
	}
	else if (tag == "LIGHTSOURCE") {
		sc->SetSprite(ResourceManager::GetSpriteSheet("campfire")->GetSpriteAtIndex(0));
	}

	_pHealth = AddComponent(new StructureHealth(this, 100));
}
