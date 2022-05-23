#include "StructureObject.h"
#include "StructureHealth.h"

StructureObject::StructureObject(std::string name, std::string tag)
	:  GameObject(name, tag)
{
	if (tag == "WALL") {
		AddComponent(new Texture2D("Resources/Images/Wall.png", true));
	}
	else {
		AddComponent(new Texture2D("Resources/Images/Tower.png", true));
	}

	_pHealth = AddComponent(new StructureHealth(this, 10));
}
