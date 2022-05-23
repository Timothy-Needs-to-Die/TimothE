#pragma once
#include "ItemConfig.h"

struct ResourceCost {
	int woodRequired = 0;
	int stoneRequired = 0;
	int metalRequired = 0;
	int coalRequired = 0;
};

struct PurchaseableConfig : ItemConfig {
	int price;
	ResourceCost resourceCost;
	bool useResourceCost; 

};

