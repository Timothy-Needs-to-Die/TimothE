#include "InventoryScreen.h"

InventoryScreen::InventoryScreen(string name, string tag) : GameObject(name, tag)
{
	AddComponent(ResourceManager::GetTexture("planks"));
	AddComponent(new TextComponent(this));
	GetComponent<TextComponent>()->SetText("Inventory");
	_pInventoryBody = new GameObject("InventoryBody", "UI");
	_pInventoryBody->AddComponent(new TextComponent(_pInventoryBody));
	_pInventoryBody->GetComponent<TextComponent>()->SetText("5");
}
