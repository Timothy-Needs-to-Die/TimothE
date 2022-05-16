#include "BaseTrader.h"
#include "PlayerResourceManager.h"
#include "PlantResourceType.h"
#include "CoreResourceType.h"
#include "ItemResourceType.h"



BaseTrader::BaseTrader(TraderConfig config)
{
	SetTraderConfig(config);
}

BaseTrader::~BaseTrader()
{
}

void BaseTrader::OnNewDay()
{
	GenerateDailyGoldAmmount();
}


void BaseTrader::OnBuy(ItemConfig item, PlantResourceType type, int ammount)
{
	if (PlayerResourceManager::GetPlantResource(type)->CanAfford(item.price * ammount)) {
		PlayerResourceManager::GetPlantResource(type)->GainResource(ammount);
		std::cout << "[LOG: BaseTrader::OnBuy: Item bought by player" << std::endl;
	}
	else {
		std::cout << "[LOG: BaseTrader::OnBuy: Player can not afford item" << std::endl; 
	}
}

void BaseTrader::OnBuy(ItemConfig item, HotbarItem type, int ammount)
{
	if (PlayerResourceManager::GetHotbarItem(type)->CanAfford(item.price * ammount)) {
		PlayerResourceManager::GetHotbarItem(type)->GainResource(ammount);
		std::cout << "[LOG: BaseTrader::OnBuy: Item bought by player" << std::endl;
	}
	else {
		std::cout << "[LOG: BaseTrader::OnBuy: Player can not afford item" << std::endl; 
	}
}

void BaseTrader::OnSell()
{
}

void BaseTrader::UpdateUI()
{
	//Update UI to display refreshed values of trader/UI
}

void BaseTrader::LevelUpTrader()
{
	_traderLevel++;
}

void BaseTrader::SetTraderConfig(TraderConfig config)
{
	_config = config;

}

void BaseTrader::GenerateDailyGoldAmmount()
{
}
