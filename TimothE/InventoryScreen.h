#pragma once
#include "Texture2D.h"
#include "TextComponent.h"
#include "PlayerResourceManager.h"
class InventoryScreen : public GameObject
{
public:
	InventoryScreen(string name = "InventoryScreen", string tag = "UI");

	void OnUpdate();

	void SetAllActive(bool val);
	bool GetAllActive();

	

private:
	GameObject* _pInventoryTitle;
	GameObject* _pInventoryBody;

	void Display();
};

