#pragma once
#include "Component.h"
#include "TraderConfig.h"
#include "ItemConfig.h"


class PlayerResourceManager;
enum PlantResourceType; 
enum CoreResourceType;
struct HotbarItem;

class BaseTrader : Component
{
public:
	BaseTrader(TraderConfig config);
	~BaseTrader();
	
	COMPONENT_STATIC_TYPE(Trader_Type);


	void OnNewDay();


	void OnBuy(ItemConfig item, PlantResourceType type, int ammount);
	void OnBuy(ItemConfig item, HotbarItem type, int ammount);

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
