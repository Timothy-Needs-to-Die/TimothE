#pragma once
#include "Component.h"
#include "TraderConfig.h"
#include "ItemConfig.h"
#include <string>
#include "ToolConfig.h"
#include "ArmourConfig.h"

class CSVReader;
class PlayerResourceManager;
enum PlantResourceType; 
enum CoreResourceType;
struct HotbarItem;

class BaseTrader : Component
{
public:
	BaseTrader(std::string configPath, std::string name);
	~BaseTrader();
	
	COMPONENT_STATIC_TYPE(Trader_Type);


	void OnNewDay();


	void OnBuy(ItemConfig item, PlantResourceType type, int amount);
	//void OnBuy(ItemConfig item, HotbarItem type, int amount);

	void OnSell();
	void UpdateUI();
	void LevelUpTrader();
	TraderConfig* GetConfig() { return &_config; }

	void SetTraderConfig(std::string configPath);
private:
	void GenerateDailyGoldamount();
	TraderConfig _config; 

	int _traderLevel;
	int _goldAtLevel[4];
    int _traderGold;


};


//base trader component will be attatched to gameObject
