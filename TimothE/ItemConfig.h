#pragma once

#include <string>
class PlayerResourceManager;


struct ItemConfig
{
	Type type;
	float price;
	std::string name; 
};

enum Type {
	hotbar,
	plant
};