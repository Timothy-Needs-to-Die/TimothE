#include "InventoryScreen.h"
#include "SceneManager.h"

InventoryScreen::InventoryScreen(string name, string tag) : GameObject(name, tag)
{
	_pInventoryTitle = new GameObject("InventoryTitle", "UI");
	_pInventoryTitle->SetChild(new GameObject("Column1", "UI"));
	_pInventoryTitle->AddComponent(new TextComponent(_pInventoryTitle));
	_pInventoryTitle->GetChild()->AddComponent(new TextComponent(_pInventoryTitle->GetChild()));
	
	SceneManager::GetCurrentScene()->AddGameObject(_pInventoryTitle);

	_pInventoryBody = new GameObject("InventoryBody", "UI");
	_pInventoryBody->AddComponent(new TextComponent(_pInventoryBody));
	_pInventoryBody->SetChild(new GameObject("Column2", "UI"));
	_pInventoryBody->GetChild()->AddComponent(new TextComponent(_pInventoryBody->GetChild()));
	_pInventoryBody->GetChild()->SetChild(new GameObject("Column3", "UI"));
	_pInventoryBody->GetChild()->GetChild()->AddComponent(new TextComponent(_pInventoryBody->GetChild()->GetChild()));
	
	Display();
	SceneManager::GetCurrentScene()->AddGameObject(_pInventoryBody);
}

void InventoryScreen::SetAllActive(bool val) {
	SetActive(val);
	_pInventoryTitle->SetActive(val);
	_pInventoryTitle->GetChild()->SetActive(val);
	_pInventoryBody->SetActive(val);
	_pInventoryBody->GetChild()->SetActive(val);
	_pInventoryBody->GetChild()->GetChild()->SetActive(val);
}

bool InventoryScreen::GetAllActive()
{
	return _pInventoryTitle->IsActive();
}

void InventoryScreen::Display()
{
	_pInventoryTitle->GetTransform()->SetPosition(0.0f, 1000.0f);
	_pInventoryTitle->GetComponent<TextComponent>()->SetScale(2.0f);
	_pInventoryTitle->GetComponent<TextComponent>()->SetColor({ 0.0f, 0.0f, 0.0f });
	_pInventoryTitle->GetComponent<TextComponent>()->SetFont("comic.ttf");
	_pInventoryTitle->GetChild()->GetTransform()->SetPosition(500.0f, 1000.0f);
	_pInventoryTitle->GetChild()->GetComponent<TextComponent>()->SetScale(1.0f);
	_pInventoryTitle->GetChild()->GetComponent<TextComponent>()->SetColor({ 0.96f, 0.81f, 0.0f });
	_pInventoryTitle->GetChild()->GetComponent<TextComponent>()->SetFont("comic.ttf");
	_pInventoryBody->GetTransform()->SetPosition(5.0f, 950.0f);
	_pInventoryBody->GetComponent<TextComponent>()->SetScale(1.0f);
	_pInventoryBody->GetComponent<TextComponent>()->SetColor({ 0.0f, 0.0f, 0.0f });
	_pInventoryBody->GetChild()->GetTransform()->SetPosition(450.0f, 950.0f);
	_pInventoryBody->GetChild()->GetComponent<TextComponent>()->SetScale(1.0f);
	_pInventoryBody->GetChild()->GetComponent<TextComponent>()->SetColor({ 0.0f, 0.0f, 0.0f });
	_pInventoryBody->GetChild()->GetChild()->GetTransform()->SetPosition(1050.0f, 950.0f);
	_pInventoryBody->GetChild()->GetChild()->GetComponent<TextComponent>()->SetScale(1.0f);
	_pInventoryBody->GetChild()->GetChild()->GetComponent<TextComponent>()->SetColor({ 0.0f, 0.0f, 0.0f });
}

void InventoryScreen::OnUpdate()
{
	string text;
	text += "\nWood: " + std::to_string(PlayerResourceManager::GetCoreResource(Wood)->GetAmount());
	text += "\nStone: " + std::to_string(PlayerResourceManager::GetCoreResource(Stone)->GetAmount());
	text += "\nMetal: " + std::to_string(PlayerResourceManager::GetCoreResource(Metal)->GetAmount());
	text += "\nCoal: " + std::to_string(PlayerResourceManager::GetCoreResource(Coal)->GetAmount());
	_pInventoryBody->GetComponent<TextComponent>()->SetText(text);
	text.clear();
	text += "\nWheat Seed: " + std::to_string(PlayerResourceManager::GetPlantResource(WheatSeedRes)->GetAmount());
	text += "\nCarrot Seed: " + std::to_string(PlayerResourceManager::GetPlantResource(CarrotSeedRes)->GetAmount());
	text += "\nPotato Seed: " + std::to_string(PlayerResourceManager::GetPlantResource(PotatoSeedRes)->GetAmount());
	text += "\nApple Seed: " + std::to_string(PlayerResourceManager::GetPlantResource(AppleSeedRes)->GetAmount());
	_pInventoryBody->GetChild()->GetComponent<TextComponent>()->SetText(text);
	text.clear();
	text += "\nWheat: " + std::to_string(PlayerResourceManager::GetPlantResource(WheatRes)->GetAmount());
	text += "\nCarrot: " + std::to_string(PlayerResourceManager::GetPlantResource(CarrotRes)->GetAmount());
	text += "\nPotato: " + std::to_string(PlayerResourceManager::GetPlantResource(PotatoRes)->GetAmount());
	text += "\nApple: " + std::to_string(PlayerResourceManager::GetPlantResource(AppleRes)->GetAmount());
	_pInventoryBody->GetChild()->GetChild()->GetComponent<TextComponent>()->SetText(text);

	_pInventoryTitle->GetComponent<TextComponent>()->SetText("Inventory");
	_pInventoryTitle->GetChild()->GetComponent<TextComponent>()->SetText("Gold: " + std::to_string(PlayerResourceManager::GetCoreResource(Gold)->GetAmount()));

	Display();
}