#pragma once 
#include "PurchaseableConfig.h"

enum ArmourType {
	Leather,
	Chainmail,
	Iron
};

struct ArmourConfig : PurchaseableConfig {
	ArmourConfig() = default;
	ArmourType type;
	int damageReduction;
};