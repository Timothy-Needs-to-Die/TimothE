#pragma once
#include "CoreResourceType.h"
#include "PlantResourceType.h"
//#include "ItemResourceType.h"
#include <iostream>
#include "ItemConfig.h"

class PlayerResource
{ 
public:
	PlayerResource(int amount);
	PlayerResource() = default;
	~PlayerResource();

	bool CanAfford(int amount);
	void SpendResource(int amount);
	void GainResource(int amount);
	int GetAmount() const { return _amount; }

private:

	ItemConfig _config; 
	int _amount; 
};
