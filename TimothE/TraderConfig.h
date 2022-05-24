#pragma once
#include "ToolConfig.h"
#include "PlantResourceType.h"
#include "ArmourConfig.h"
#include <set>

enum TraderType
{
	Builder, // Screw the builder
	Blacksmith,
	Armourer,
	Wizard, // The wizzard shall not exist 
	Farmer   
};


struct TraderConfig
{
	TraderType type;
	int goldAtLevel[4] = {100, 200, 300, 400};
	std::vector<PurchaseableConfig> itemsToSell;
	//std::set<PurchaseableConfig> itemsToSell;
}; 

