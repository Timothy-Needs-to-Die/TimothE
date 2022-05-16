#pragma once
#include "ItemResourceType.h"
#include "PlantResourceType.h"

struct TraderConfig
{
	TraderType type;
	int goldAtLevel[4];
	TraderInventory  inventory;

}; 

struct TraderInventory {
	std::vector<HotbarItem> hotbarItemsToSell;
	std::vector<PlantResourceType> plantItemsToSell;
};

enum TraderType
{
	Builder,
	Blacksmith,
	Armourer,
	Wizard,
	Farmer   
};