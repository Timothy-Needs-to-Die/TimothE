#pragma once
#include "ToolConfig.h"
#include "PlantResourceType.h"
#include "ArmourConfig.h"

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

}; 

