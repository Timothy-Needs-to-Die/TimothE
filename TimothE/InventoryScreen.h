#pragma once
#include "Texture2D.h"
#include "TextComponent.h"
#include "PlayerResourceManager.h"
class InventoryScreen : public GameObject
{
public:
	InventoryScreen(string name = "InventoryScreen", string tag = "UI");

private:
	
	GameObject* _pInventoryBody;
};

