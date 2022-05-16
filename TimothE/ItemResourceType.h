#pragma once 

struct HotbarItem
{
	ItemType type;
	float damagePerHit;
	int level;
};

enum ItemType
{
	Axe,
	Pickaxe,
	Sword
};