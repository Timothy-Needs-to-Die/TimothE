#include "StructureObject.h"
#include "StructureHealth.h"

StructureObject::StructureObject(std::string name, std::string tag)
	:  GameObject(name, tag)
{
	if (tag == "WALL") {
		AddComponent(ResourceManager::GetTexture("wall"));
	}
	else {
		AddComponent(ResourceManager::GetTexture("lenna"));
	}

	_pHealth = AddComponent(new StructureHealth(this, 10));
}
