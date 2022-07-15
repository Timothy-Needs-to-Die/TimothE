#pragma once
#include "Component.h"
#include "TraderConfig.h"
#include "ItemConfig.h"
#include <string>
#include "ToolConfig.h"
#include "ArmourConfig.h"
#include "SeedConfig.h"
#include "CropConfig.h"

class CSVReader;
class PlayerResourceManager;
enum PlantResourceType; 
enum class CoreResourceType;
struct HotbarItem;

class BaseTrader : Component
{
public:
	BaseTrader(std::string configPath, std::string name);
	~BaseTrader();
	
	COMPONENT_STATIC_TYPE(Trader_Type);


	void OnNewDay();


	//void OnBuy(PurchaseableConfig item);
	void OnBuyTool(ToolConfig tool);
	void OnBuySeed(SeedConfig seed);

	void OnBuyArmour(ArmourConfig armour);

	void OnSellCrop(CropConfig crop);
	
	//void OnBuy(ItemConfig item, HotbarItem type, int amount);

	//void OnSell();
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
