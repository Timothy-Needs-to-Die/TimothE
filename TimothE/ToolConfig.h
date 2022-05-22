#pragma once
#include "PurchaseableConfig.h"

enum ToolType {
	Sword,
	Pickaxe,
	Axe
};

struct ToolConfig : PurchaseableConfig {
	ToolConfig() = default;
	ToolType type;
	int currentLevel;
	int damagePerHit;
	int townLevelRequired;
};

