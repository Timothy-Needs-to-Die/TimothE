#pragma once
#include <map>
#include "PlayerResource.h"


static class PlayerResourceManager
{
public:
	PlayerResourceManager();
	~PlayerResourceManager();

	//Gets the desired resource enabling you to access the functions of PlayerResource
	static PlayerResource* GetCoreResource(CoreResourceType type);
	static PlayerResource* GetPlantResource(PlantResourceType type);
	static PlayerResource* GetHotbarItem(HotbarItem item);

private:
	static std::map<CoreResourceType, PlayerResource> _coreResourceMap;
	static std::map<PlantResourceType, PlayerResource> _plantResourceMap;
	static std::map<HotbarItem, PlayerResource> _hotbarItemMap; 

}; 


//The maps contain the type and resource object, meaning adding a wood resource will mean calling GetCoreResource
//Then calling GainResource from the stored PlayerResource

//Hotbar assignment of tools/weapons will be done automatically based on the type (E.g pickaxe = 1, axe = 2, sword = 3)