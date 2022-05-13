#include "BaseTrader.h"

BaseTrader::BaseTrader()
{
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

void BaseTrader::Trade(Item item)
{
}

void BaseTrader::OnBuy(Item item)
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
