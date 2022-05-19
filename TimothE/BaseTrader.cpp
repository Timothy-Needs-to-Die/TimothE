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
	GenerateDailyGoldamount();
}

//
//void BaseTrader::OnBuy(ItemConfig item, PlantResourceType type, int amount)
//{
//	if (PlayerResourceManager::GetPlantResource(type)->CanAfford(item.price * amount)) {
//		PlayerResourceManager::GetPlantResource(type)->GainResource(amount);
//		std::cout << "[LOG: BaseTrader::OnBuy: Item bought by player" << std::endl;
//	}
//	else {
//		std::cout << "[LOG: BaseTrader::OnBuy: Player can not afford item" << std::endl; 
//	}
//}

//void BaseTrader::OnBuy(ItemConfig item, HotbarItem type, int amount)
//{
//	if (PlayerResourceManager::GetHotbarItem(type)->CanAfford(item.price * amount)) {
//		PlayerResourceManager::GetHotbarItem(type)->GainResource(amount);
//		std::cout << "[LOG: BaseTrader::OnBuy: Item bought by player" << std::endl;
//	}
//	else {
//		std::cout << "[LOG: BaseTrader::OnBuy: Player can not afford item" << std::endl; 
//	}
//}

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

void BaseTrader::GenerateDailyGoldamount()
{
}
