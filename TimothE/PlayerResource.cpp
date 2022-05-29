#include "pch.h"
#include "PlayerResource.h"
#include "Core.h"

PlayerResource::PlayerResource(int amount)
{
	_amount = amount;
}

PlayerResource::~PlayerResource()
{
}

bool PlayerResource::CanAfford(int amount)
{
	return _amount >= amount;
}

void PlayerResource::SpendResource(int amount)
{
	if (CanAfford(amount)) {
		_amount -= amount;
		TIM_LOG_LOG("Player Resource Spend: " << amount);
	}
	else
		TIM_LOG_LOG("Player does not have the resources to spend");
}

void PlayerResource::GainResource(int amount)
{
	TIM_LOG_LOG("Player Resource Gained: " << amount);
	_amount += amount;
}
