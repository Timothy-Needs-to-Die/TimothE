#include "BaseTrader.h"
#include "PlayerResourceManager.h"

BaseTrader::BaseTrader(TraderConfig config)
{
	_config = config;
}

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

void BaseTrader::OnBuy()
{
	
}


void BaseTrader::OnBuy(int type, ItemConfig item)
{
	//Plant Items
	if (type == 0) {
		
	}
	//Hotbar Items
	else if (type == 1) {

	}
	
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
