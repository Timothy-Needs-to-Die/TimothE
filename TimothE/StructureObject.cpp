#include "pch.h"
#include "StructureObject.h"
#include "StructureHealth.h"

StructureObject::StructureObject(std::string name, std::string tag)
	:  GameObject(name, tag)
{
	if (tag == "WALL") {
		//AddComponent(ResourceManager::GetTexture("wall"));
	}
	else if (tag == "TOWER") {
		//AddComponent(ResourceManager::GetTexture("tower"));
	}
	else if (tag == "LIGHTSOURCE") {
		//AddComponent(ResourceManager::GetTexture("campfire"));
	}

	_pHealth = AddComponent(new StructureHealth(this, 100));
}
