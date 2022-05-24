#include "InventoryScreen.h"
#include "SceneManager.h"

InventoryScreen::InventoryScreen(string name, string tag) : GameObject(name, tag)
{
	
	//_pPanel = new GameObject("Panel", "UI");
	AddComponent(ResourceManager::GetTexture("planks"));
	GetTransform()->SetPosition(-0.3f, -0.3f);
	GetTransform()->SetScale({ 0.25f, 0.25f });
	//SceneManager::GetCurrentScene()->AddGameObject(_pPanel);
	
	_pInventoryTitle = new GameObject("InventoryTitle", "UI");
	_pInventoryTitle->AddComponent(new TextComponent(_pInventoryTitle));
	_pInventoryTitle->GetComponent<TextComponent>()->SetText("Inventory");
	_pInventoryTitle->GetTransform()->SetPosition(10.0f, 10.0f);
	SceneManager::GetCurrentScene()->AddGameObject(_pInventoryTitle);

	_pInventoryBody = new GameObject("InventoryBody", "UI");
	_pInventoryBody->AddComponent(new TextComponent(_pInventoryBody));
	_pInventoryBody->GetComponent<TextComponent>()->_scale = 0.5f;
	Display();
	SceneManager::GetCurrentScene()->AddGameObject(_pInventoryBody);
}

void InventoryScreen::SetAllActive(bool val) {
	//_pPanel->SetActive(val);
	SetActive(val);
	_pInventoryTitle->SetActive(val);
	_pInventoryBody->SetActive(val);
}

bool InventoryScreen::GetAllActive()
{
	return _pInventoryTitle->IsActive();
}

void InventoryScreen::Display()
{
	_pInventoryTitle->GetTransform()->SetPosition(100.0f, 100.0f);
	_pInventoryBody->GetTransform()->SetPosition(200.0f, 200.0f);
}

void InventoryScreen::OnUpdate()
{
	string text;
	text += "Wood: " + std::to_string(PlayerResourceManager::GetCoreResource(Wood)->GetAmount());
	text += "\nStone: " + std::to_string(PlayerResourceManager::GetCoreResource(Stone)->GetAmount());
	text += "\nMetal: " + std::to_string(PlayerResourceManager::GetCoreResource(Metal)->GetAmount());
	text += "\nGold: " + std::to_string(PlayerResourceManager::GetCoreResource(Gold)->GetAmount());
	text += "\nCoal: " + std::to_string(PlayerResourceManager::GetCoreResource(Coal)->GetAmount());
	_pInventoryBody->GetComponent<TextComponent>()->SetText(text);
	Display();
}