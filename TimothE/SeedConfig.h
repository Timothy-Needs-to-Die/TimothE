#pragma once
#include "PurchaseableConfig.h"

enum SeedType {
	WheatSeed,
	CarrotSeed,
	PotatoSeed,
	AppleSeed
};

struct SeedConfig : PurchaseableConfig {
	SeedConfig() = default;
	SeedType type;
	int growthPerDay;
};