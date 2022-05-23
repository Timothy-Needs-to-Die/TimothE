#pragma once
#include "ItemConfig.h"

struct ResourceCost {
	int woodRequired;
	int stoneRequired;
	int metalRequired;
	int coalRequired;
};

struct PurchaseableConfig : ItemConfig {
	int price;
	ResourceCost resourceCost;
	bool useResourceCost; 

};

