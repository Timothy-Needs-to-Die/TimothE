#include "pch.h"
#include "PlayerResourceManager.h"

std::unordered_map<CoreResourceType, PlayerResource> PlayerResourceManager::_coreResourceMap = std::unordered_map<CoreResourceType, PlayerResource>();
std::unordered_map<PlantResourceType, PlayerResource> PlayerResourceManager::_plantResourceMap = std::unordered_map<PlantResourceType, PlayerResource>();
//std::unordered_map<HotbarItem, PlayerResource> PlayerResourceManager::_hotbarItemMap = std::unordered_map<HotbarItem, PlayerResource>();
ArmourConfig PlayerResourceManager::_currentArmour;
ToolConfig PlayerResourceManager::_currentSword;
ToolConfig PlayerResourceManager::_currentAxe;
ToolConfig PlayerResourceManager::_currentPickaxe;
std::vector<CropSellingData> PlayerResourceManager::_cropSellingData = std::vector<CropSellingData>();

PlayerResourceManager::PlayerResourceManager()
{
	
}

PlayerResourceManager::~PlayerResourceManager()
{
	_coreResourceMap.clear();
	_plantResourceMap.clear();
	//_hotbarItemMap.clear();
}

PlayerResource* PlayerResourceManager::GetCoreResource(CoreResourceType type)
{
	return &_coreResourceMap[type];
}

PlayerResource* PlayerResourceManager::GetPlantResource(PlantResourceType type)
{
	return &_plantResourceMap[type];
}

bool PlayerResourceManager::CanAfford(const ResourceCost& cost)
{
	if(_coreResourceMap[CoreResourceType::Wood].CanAfford(cost.woodRequired) && 
		_coreResourceMap[CoreResourceType::Stone].CanAfford(cost.stoneRequired) &&
		_coreResourceMap[CoreResourceType::Metal].CanAfford(cost.metalRequired) &&
		_coreResourceMap[CoreResourceType::Coal].CanAfford(cost.coalRequired) &&
		_coreResourceMap[CoreResourceType::Gold].CanAfford(cost.goldRequired)) {
		return true;
	}

	return false;
}

void PlayerResourceManager::SpendResources(const ResourceCost& cost)
{
	_coreResourceMap[CoreResourceType::Wood].SpendResource(cost.woodRequired);
	_coreResourceMap[CoreResourceType::Metal].SpendResource(cost.metalRequired);
	_coreResourceMap[CoreResourceType::Stone].SpendResource(cost.stoneRequired);
	_coreResourceMap[CoreResourceType::Coal].SpendResource(cost.coalRequired);

}
void PlayerResourceManager::SetTool(ToolConfig tool)
{
	if (tool.type == ToolType::Pickaxe) {
		_currentPickaxe = tool;
	}
	else if (tool.type == ToolType::Axe) {
		_currentAxe = tool;
	}
	else if (tool.type == ToolType::Sword) {
		_currentSword = tool;
	}

}

void PlayerResourceManager::SetArmour(ArmourConfig armour)
{
	_currentArmour = armour;
}

void PlayerResourceManager::SellAll()
{
	int totalIncome = 0;

	for (CropSellingData cropConfig : _cropSellingData)
	{
		if (cropConfig.type == WheatRes)
		{
			int wheatAmount = _plantResourceMap[WheatRes].GetAmount();
			totalIncome += wheatAmount * cropConfig.sellPrice;
			_plantResourceMap[WheatRes].SpendResource(wheatAmount);
		}

		if (cropConfig.type == PotatoRes)
		{
			int potatoAmount = _plantResourceMap[PotatoRes].GetAmount();
			totalIncome += potatoAmount * cropConfig.sellPrice;
			_plantResourceMap[PotatoRes].SpendResource(potatoAmount);
		}

		if (cropConfig.type == CarrotRes)
		{
			int carrotAmount = _plantResourceMap[CarrotRes].GetAmount();
			totalIncome += carrotAmount * cropConfig.sellPrice;
			_plantResourceMap[CarrotRes].SpendResource(carrotAmount);
		}
	}

	PlayerResourceManager::GetCoreResource(CoreResourceType::Gold)->GainResource(totalIncome);
}

void PlayerResourceManager::BuyCrop(PlantResourceType type)
{
	for (CropSellingData cropConfig : _cropSellingData)
	{
		if (cropConfig.rawType == type)
		{
			if (_coreResourceMap[CoreResourceType::Gold].CanAfford(cropConfig.buyPrice))
			{
				_plantResourceMap[type].GainResource(1);
				_coreResourceMap[CoreResourceType::Gold].SpendResource(cropConfig.buyPrice);
			}
		}
	}
}

void PlayerResourceManager::LoadInCropData()
{
	std::vector<std::vector<std::string>> loadedData = CSVReader::RequestDataFromFile("Resources/Data/SeedsConfig.csv");
	std::vector<std::vector<std::string>> loadedData2 = CSVReader::RequestDataFromFile("Resources/Data/CropsConfig.csv");
	for (int i = 0; i < loadedData.size(); i++)
	{
		CropSellingData	newConfig;

		newConfig.sellPrice = std::stoi(loadedData2[i][2]);
		newConfig.type = (PlantResourceType)std::stoi(loadedData[i][9]);
		newConfig.rawType = (PlantResourceType)std::stoi(loadedData[i][5]);
		newConfig.buyPrice = std::stoi(loadedData[i][2]);

		_cropSellingData.emplace_back(newConfig);
	}
}

//PlayerResource* PlayerResourceManager::GetHotbarItem(HotbarItem item)
//{
//	return &_hotbarItemMap[item];
//}


