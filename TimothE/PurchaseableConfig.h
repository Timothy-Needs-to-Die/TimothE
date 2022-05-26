#pragma once
#include "ItemConfig.h"
#include <string>
struct ResourceCost {
	int woodRequired = 0;
	int stoneRequired = 0;
	int metalRequired = 0;
	int coalRequired = 0;
	int goldRequired = 0;
};

struct PurchaseableConfig : ItemConfig {
	std::string name;
	int price;
	ResourceCost resourceCost;
	bool useResourceCost; 
	int townLevelRequired;

};

