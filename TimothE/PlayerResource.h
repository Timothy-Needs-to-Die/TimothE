#pragma once
#include "CoreResourceType.h"
#include "PlantResourceType.h"
#include "ItemResourceType.h"
#include <iostream>

class PlayerResource
{
public:
	PlayerResource(int ammount);
	PlayerResource() = default;
	~PlayerResource();

	bool CanAfford(int ammount);
	void SpendResource(int ammount);
	void GainResource(int ammount);

private:

	int _ammount; 
};
