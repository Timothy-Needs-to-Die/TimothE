#pragma once 
#include "SellableConfig.h"

enum CropType {
	Wheat,
	Carrot,
	Potato,
	Apple
};

struct SeedConfig : SellableConfig {
	CropType type;
	int price;
	int growthRate;
};

struct CropConfig : SellableConfig {
	CropType type;
};

