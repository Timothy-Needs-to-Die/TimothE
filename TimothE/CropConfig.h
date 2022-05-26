#pragma once 
#include "SellableConfig.h"
#include "PlantResourceType.h"

enum CropType {
	Wheat,
	Carrot,
	Potato,
	Apple
};

//struct SeedConfig : PurchaseableConfig {
//	CropType type;
//	int price;
//	int growthRate;
//};

struct CropConfig : SellableConfig {
	PlantResourceType type;
	int growthRate;
	int quality;
	int startSpriteIndex;
	int yield;
	PlantResourceType produceType;
};

