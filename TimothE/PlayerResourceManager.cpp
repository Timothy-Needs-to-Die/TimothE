#include "PlayerResourceManager.h"

std::unordered_map<CoreResourceType, PlayerResource> PlayerResourceManager::_coreResourceMap = std::unordered_map<CoreResourceType, PlayerResource>();
std::unordered_map<PlantResourceType, PlayerResource> PlayerResourceManager::_plantResourceMap = std::unordered_map<PlantResourceType, PlayerResource>();
//std::unordered_map<HotbarItem, PlayerResource> PlayerResourceManager::_hotbarItemMap = std::unordered_map<HotbarItem, PlayerResource>();
ArmourConfig PlayerResourceManager::_currentArmour;
ToolConfig PlayerResourceManager::_currentSword;
ToolConfig PlayerResourceManager::_currentAxe;
ToolConfig PlayerResourceManager::_currentPickaxe;

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

bool PlayerResourceManager::CanAfford(const ResourceCost& cost)
{
	if(_coreResourceMap[Wood].CanAfford(cost.woodRequired) && 
		_coreResourceMap[Stone].CanAfford(cost.stoneRequired) &&
		_coreResourceMap[Metal].CanAfford(cost.metalRequired) &&
		_coreResourceMap[Coal].CanAfford(cost.coalRequired) &&
		_coreResourceMap[Gold].CanAfford(cost.goldRequired)) {
		return true;
	}

	return false;
}

void PlayerResourceManager::SpendResources(const ResourceCost& cost)
{
	_coreResourceMap[Wood].SpendResource(cost.woodRequired);
	_coreResourceMap[Metal].SpendResource(cost.metalRequired);
	_coreResourceMap[Stone].SpendResource(cost.stoneRequired);
	_coreResourceMap[Coal].SpendResource(cost.coalRequired);

}
void PlayerResourceManager::SetTool(ToolConfig tool)
{
	if (tool.type == ToolType::Pickaxe) {
		_currentPickaxe = tool;
	}
	else if (tool.type == ToolType::Axe) {
		_currentAxe = tool;
	}
	else if (tool.type == ToolType::Sword) {
		_currentSword = tool;
	}

}

void PlayerResourceManager::SetArmour(ArmourConfig armour)
{
	_currentArmour = armour;
}

//PlayerResource* PlayerResourceManager::GetHotbarItem(HotbarItem item)
//{
//	return &_hotbarItemMap[item];
//}


