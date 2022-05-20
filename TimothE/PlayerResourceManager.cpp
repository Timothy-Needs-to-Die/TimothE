#include "PlayerResourceManager.h"

std::unordered_map<CoreResourceType, PlayerResource> PlayerResourceManager::_coreResourceMap = std::unordered_map<CoreResourceType, PlayerResource>();
std::unordered_map<PlantResourceType, PlayerResource> PlayerResourceManager::_plantResourceMap = std::unordered_map<PlantResourceType, PlayerResource>();
//std::unordered_map<HotbarItem, PlayerResource> PlayerResourceManager::_hotbarItemMap = std::unordered_map<HotbarItem, PlayerResource>();

PlayerResourceManager::PlayerResourceManager()
{
	
}

PlayerResourceManager::~PlayerResourceManager()
{
	_coreResourceMap.clear();
	_plantResourceMap.clear();
	//_hotbarItemMap.clear();
}

PlayerResource* PlayerResourceManager::GetCoreResource(CoreResourceType type)
{
	return &_coreResourceMap[type];
}

PlayerResource* PlayerResourceManager::GetPlantResource(PlantResourceType type)
{
	return &_plantResourceMap[type];
}

//PlayerResource* PlayerResourceManager::GetHotbarItem(HotbarItem item)
//{
//	return &_hotbarItemMap[item];
//}


