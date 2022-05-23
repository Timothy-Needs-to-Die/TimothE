#pragma once
#include "ToolConfig.h"
#include "PlantResourceType.h"
#include "ArmourConfig.h"
#include <set>

enum TraderType
{
	Builder,
	Blacksmith,
	Armourer,
	Wizard,
	Farmer   
};


struct TraderConfig
{
	TraderType type;
	int goldAtLevel[4] = {100, 200, 300, 400};
	std::vector<PurchaseableConfig> itemsToSell;
	//std::set<PurchaseableConfig> itemsToSell;
}; 

