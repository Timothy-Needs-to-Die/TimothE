#pragma once
#include "PurchaseableConfig.h"

enum SeedType {
	WheatSeed,
	CarrotSeed,
	PotatoSeed,
	AppleSeed
};

struct SeedConfig {
	SeedConfig() = default;
	SeedType type;
};