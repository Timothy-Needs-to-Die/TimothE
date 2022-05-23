#include "PlayerResource.h"

PlayerResource::PlayerResource(int amount)
{
	_amount = amount;
}

PlayerResource::~PlayerResource()
{
}

bool PlayerResource::CanAfford(int amount)
{

	return _amount > amount;

	
}

void PlayerResource::SpendResource(int amount)
{
	if (CanAfford(amount)) {
		_amount -= amount;
		std::cout << "[LOG: PlayerResouce::SpendResource]: Player Resource spent: " << amount << std::endl;
	}
	else
		std::cout << "[LOG: PlayerResouce::SpendResource]: Player does not have the resources to spend: " << amount << std::endl;
}

void PlayerResource::GainResource(int amount)
{
	std::cout << "[LOG: PlayerResouce::GainResource]: Player Resource Gained: " << amount << std::endl;
	_amount += amount;
}
