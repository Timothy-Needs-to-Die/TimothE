#pragma once
#include "ItemResourceType.h"
#include "PlantResourceType.h"

enum TraderType
{
	Builder,
	Blacksmith,
	Armourer,
	Wizard,
	Farmer   
};

struct TraderInventory {
	//std::vector<HotbarItem> hotbarItemsToSell;
	std::vector<PlantResourceType> plantItemsToSell;
};


struct TraderConfig
{
	TraderType type;
	int goldAtLevel[4];
	TraderInventory  inventory;

}; 

