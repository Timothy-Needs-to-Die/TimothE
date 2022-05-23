#include "BaseTrader.h"
#include "PlayerResourceManager.h"
#include "PlantResourceType.h"
#include "CoreResourceType.h"
#include "ItemResourceType.h"
#include "CSVReader.h"


BaseTrader::BaseTrader(std::string configPath, std::string name)
{
	SetTraderConfig(configPath);
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
void BaseTrader::OnBuy(PurchaseableConfig item){
	//If the item is in the traders inventory (shouldnt be necesarry if UI is set up correctly
	if (std::find(_config.itemsToSell.begin(), _config.itemsToSell.end(), item) != _config.itemsToSell.end()) {
		

	}
}

void BaseTrader::OnBuyTool(ToolConfig tool)
{
	if (_config.type == TraderType::Blacksmith) {
		if (PlayerResourceManager::CanAfford(tool.resourceCost)) {
			PlayerResourceManager::GetCoreResource(CoreResourceType::Wood)->SpendResource(tool.resourceCost.woodRequired);
			PlayerResourceManager::GetCoreResource(CoreResourceType::Stone)->SpendResource(tool.resourceCost.stoneRequired);
			PlayerResourceManager::GetCoreResource(CoreResourceType::Metal)->SpendResource(tool.resourceCost.metalRequired);
			PlayerResourceManager::GetCoreResource(CoreResourceType::Coal)->SpendResource(tool.resourceCost.coalRequired);
			PlayerResourceManager::GetCoreResource(CoreResourceType::Gold)->SpendResource(tool.resourceCost.goldRequired);
			PlayerResourceManager::SetTool(tool);
		}
		else
		{
			//Player cannot afford the item, throw text message to them saying so
		}
	}
	
}

void BaseTrader::OnBuySeed(SeedConfig seed)
{
	if (_config.type == TraderType::Farmer) {
		if(PlayerResourceManager::GetPlantResource((PlantResourceType)seed.type)->CanAfford(seed.price)
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


//When loading the trader configs, for farmer load SeedsConfig
void BaseTrader::SetTraderConfig(std::string configPath)
{
	//_config = config;
	std::vector<std::vector<std::string>> loadedData = CSVReader::RequestDataFromFile(configPath);
	
	//ignore magic numbers
	TraderConfig newConfig;
	newConfig.type = (TraderType)std::stoi(loadedData[0][11]);

	//If the trader type is a blacksmith, fill the traders inventory accordingly (YES THIS IS TERRIBLE, FOR NOW)
	if (newConfig.type == TraderType::Blacksmith) {
		for (int i = 0; i < loadedData.size(); i++)
		{
			ToolConfig traderItem;
			traderItem.name = loadedData[i][1];
			traderItem.townLevelRequired = std::stoi(loadedData[i][0]);
			traderItem.description = loadedData[i][2];
			traderItem.type = (ToolType)std::stoi(loadedData[i][10]);
			traderItem.price = std::stoi(loadedData[i][2]);
			traderItem.resourceCost.woodRequired = std::stoi(loadedData[i][4]);
			traderItem.resourceCost.stoneRequired = std::stoi(loadedData[i][5]);
			traderItem.resourceCost.metalRequired = std::stoi(loadedData[i][6]);
			traderItem.resourceCost.coalRequired = std::stoi(loadedData[i][7]);
			traderItem.damagePerHit = std::stoi(loadedData[i][8]);
			traderItem.useResourceCost = true;
			newConfig.itemsToSell.push_back(traderItem);
		}
	}
	else if (newConfig.type == TraderType::Armourer) {
		for (int i = 0; i < loadedData.size(); i++)
		{
			ArmourConfig traderItem;
			traderItem.name = loadedData[i][1];
			traderItem.townLevelRequired = std::stoi(loadedData[i][0]);
			traderItem.description = loadedData[i][2];
			traderItem.type = (ArmourType)std::stoi(loadedData[i][10]);
			traderItem.price = std::stoi(loadedData[i][2]);
			traderItem.resourceCost.woodRequired = std::stoi(loadedData[i][4]);
			traderItem.resourceCost.stoneRequired = std::stoi(loadedData[i][5]);
			traderItem.resourceCost.metalRequired = std::stoi(loadedData[i][6]);
			traderItem.resourceCost.coalRequired = std::stoi(loadedData[i][7]);
			traderItem.damageReduction = std::stoi(loadedData[i][8]);
			traderItem.useResourceCost = true;
			newConfig.itemsToSell.push_back(traderItem);
		}
	}
	else if (newConfig.type == TraderType::Farmer) {
		for (int i = 0; i < loadedData.size(); i++){

			SeedConfig traderItem;
			traderItem.name = loadedData[i][1];
			traderItem.townLevelRequired = std::stoi(loadedData[i][0]);
			traderItem.price = std::stoi(loadedData[i][2]);
			traderItem.description = loadedData[i][3];
			traderItem.type = (SeedType)std::stoi(loadedData[i][5]);
			traderItem.growthPerDay = std::stoi(loadedData[i][4]);
			newConfig.itemsToSell.push_back(traderItem);
		}
		
	}
	
	
			
	//have an if statement per trader type that defines how its inventory is loaded

}

void BaseTrader::GenerateDailyGoldamount()
{
}
