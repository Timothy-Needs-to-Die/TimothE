#pragma once
#include <map>
#include <unordered_map>
#include "PlayerResource.h"
#include "ItemResourceType.h"
#include "ItemConfig.h"
#include "PurchaseableConfig.h"
#include "ToolConfig.h"
#include "ArmourConfig.h"


static class PlayerResourceManager
{
public:
	PlayerResourceManager();
	~PlayerResourceManager();

	//Gets the desired resource enabling you to access the functions of PlayerResource
	static PlayerResource* GetCoreResource(CoreResourceType type);
	static PlayerResource* GetPlantResource(PlantResourceType type);
	

	static bool CanAfford(const ResourceCost& cost);
	static void SpendResources(const ResourceCost& cost);
	//static bool CanAfford(int gold);
	//static PlayerResource* GetHotbarItem(HotbarItem item);

	static void SetTool(ToolConfig tool);
	static void SetArmour(ArmourConfig armour);

private:
	
	static std::unordered_map<CoreResourceType, PlayerResource> _coreResourceMap;
	static std::unordered_map<PlantResourceType, PlayerResource> _plantResourceMap;
	//static std::unordered_map<ToolType, PlayerResource> _toolMap; 
	static ArmourConfig _currentArmour; 
	static ToolConfig _currentSword;
	static ToolConfig _currentPickaxe;
	static ToolConfig _currentAxe;

}; 


//The maps contain the type and resource object, meaning adding a wood resource will mean calling GetCoreResource
//Then calling GainResource from the stored PlayerResource

//Hotbar assignment of tools/weapons will be done automatically based on the type (E.g pickaxe = 1, axe = 2, sword = 3)