#pragma once
#include "ItemConfig.h"
#include <string>
struct ResourceCost {
	int woodRequired;
	int stoneRequired;
	int metalRequired;
	int coalRequired;
};

struct PurchaseableConfig : ItemConfig {
	std::string name;
	int price;
	ResourceCost resourceCost;
	bool useResourceCost; 
	int townLevelRequired;

};

