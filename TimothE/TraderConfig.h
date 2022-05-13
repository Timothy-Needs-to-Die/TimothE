#pragma once
struct TraderConfig
{
	TraderType type;
	int goldAtLevel[4];
	Item itemsToSell[];

};

enum TraderType
{
	Builder,
	Blacksmith,
	Armourer,
	Wizard,
	Farmer
};