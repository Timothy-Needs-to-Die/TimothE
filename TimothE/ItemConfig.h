#pragma once

#include <string>


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