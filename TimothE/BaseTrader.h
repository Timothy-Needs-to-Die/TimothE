#pragma once
#include "Component.h"
#include "TraderConfig.h"
#include "ItemConfig.h"

class PlayerResourceManager;

class BaseTrader : Component
{
public:
	BaseTrader(TraderConfig config);
	~BaseTrader();
	
	COMPONENT_STATIC_TYPE(Trader_Type);


	void OnNewDay();

	//Pass in 1 for hotbar items, 2 for seeds
    void OnBuy(int type, ItemConfig item);
	void OnSell();
	void UpdateUI();
	void LevelUpTrader();
	TraderConfig* GetConfig() { return &_config; }

	void SetTraderConfig(TraderConfig config);
private:
	void GenerateDailyGoldAmmount();
	TraderConfig _config; 

	int _traderLevel;
	int _goldAtLevel[4];
    int _traderGold;


};


//base trader component will be attatched to gameObject
