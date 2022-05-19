#include "PlayerResourceManager.h"

std::map<CoreResourceType, PlayerResource> PlayerResourceManager::_coreResourceMap;
std::map<PlantResourceType, PlayerResource> PlayerResourceManager::_plantResourceMap;

PlayerResourceManager::PlayerResourceManager()
{
	
}

PlayerResourceManager::~PlayerResourceManager()
{
	_coreResourceMap.clear();
	_plantResourceMap.clear();
}

PlayerResource* PlayerResourceManager::GetCoreResource(CoreResourceType type)
{
	return &_coreResourceMap[type];
}

PlayerResource* PlayerResourceManager::GetPlantResource(PlantResourceType type)
{
	return &_plantResourceMap[type];
}


