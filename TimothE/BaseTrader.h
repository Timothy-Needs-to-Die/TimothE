#pragma once

class BaseTrader
{
public:
	BaseTrader();
	~BaseTrader();
	
	void OnNewDay();
	void GenerateDailyGoldAmmount();
	void Trade(Item item);
    void OnBuy(Item item);
	void UpdateUI();


private:
	int _traderLevel;
	int _goldAtLevel[4];

protected:
	int _traderGold;
	//TraderConfig _config;
};

