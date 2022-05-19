#pragma once
#include "CoreResourceType.h"
#include "PlantResourceType.h"
#include <iostream>

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

	int _amount;
};
