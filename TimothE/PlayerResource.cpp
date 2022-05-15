#include "PlayerResource.h"

PlayerResource::PlayerResource(int ammount)
{
	_ammount = ammount;
}

PlayerResource::~PlayerResource()
{
}

bool PlayerResource::CanAfford(int ammount)
{

	return _ammount > ammount;

	
}

void PlayerResource::SpendResource(int ammount)
{
	if (CanAfford(ammount)) {
		_ammount -= ammount;
		std::cout << "[LOG: PlayerResouce::SpendResource]: Player Resource spent: " << ammount << std::endl;
	}
	else
		std::cout << "[LOG: PlayerResouce::SpendResource]: Player does not have the resources to spend: " << ammount << std::endl;
}

void PlayerResource::GainResource(int ammount)
{
	std::cout << "[LOG: PlayerResouce::GainResource]: Player Resource Gained: " << ammount << std::endl;
	_ammount += ammount;
}
