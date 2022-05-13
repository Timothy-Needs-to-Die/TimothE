#pragma once
#include "Item.h"
struct TraderConfig
{
	TraderType type;
	int goldAtLevel[4];
	std::vector<Item> itemsToSell; 

};

enum TraderType
{
	Builder,
	Blacksmith,
	Armourer,
	Wizard,
	Farmer
};