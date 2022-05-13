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
	

private:
	static std::map<CoreResourceType, PlayerResource> _coreResourceMap;
	static std::map<PlantResourceType, PlayerResource> _plantResourceMap;

};


//The maps contain the type and resource object, meaning adding a wood resource will mean calling GetCoreResource
//Then calling GainResource from the stored PlayerResource