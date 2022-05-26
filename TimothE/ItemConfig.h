#pragma once
#include <string>
#include "Sprite.h"


struct ItemConfig
{
	ItemConfig() = default;
	ItemConfig(const ItemConfig&) {};
	
	std::string description;
	Sprite* icon;
	

};

