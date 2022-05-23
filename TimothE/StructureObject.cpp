#include "StructureObject.h"
#include "StructureHealth.h"

StructureObject::StructureObject(std::string name, std::string tag)
	:  GameObject(name, tag)
{
	if (tag == "WALL") {
		AddComponent(ResourceManager::GetTexture("fish"));
	}
	else {
		AddComponent(ResourceManager::GetTexture("lenna"));
	}

	AddComponent(new StructureHealth(this, 10));
}
