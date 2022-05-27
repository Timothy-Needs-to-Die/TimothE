#include "PlayerUIComponent.h"
#include "TextObject.h"
#include "Transform.h"
#include "SceneManager.h"

PlayerUIComponent::PlayerUIComponent(GameObject* parent)
	: Component(parent)
{
	SetType(PlayerUI_Type);


	Scene* pScene = SceneManager::GetCurrentScene();

	TextObject* pBuildModeTitle = new TextObject("Build Mode", "arial.ttf");
	pBuildModeTitle->GetTransform()->SetPosition(850.0f, 1000.0f);
	pScene->AddGameObject(pBuildModeTitle);
	_pBuildModeUI.emplace_back(pBuildModeTitle);

	std::string text = "1: Wall    2: Tower    3: Campfire";
	TextObject* pControls = new TextObject(text, "arial.ttf");
	pControls->GetTransform()->SetPosition(640.0f, 950.0f);
	pScene->AddGameObject(pControls);
	_pBuildModeUI.emplace_back(pControls);

	SetBuildModeUIActive(false);

	TextObject* pFarmingModeTitle = new TextObject("Farming Mode", "arial.ttf");
	pFarmingModeTitle->GetTransform()->SetPosition(800.0f, 200.0f);
	pScene->AddGameObject(pFarmingModeTitle);
	_pFarmModeUI.emplace_back(pFarmingModeTitle);

	std::string farmText = "F: Till / Harvest   1: Wheat   2: Potato";
	TextObject* pFarmControls = new TextObject(farmText, "arial.ttf");
	pFarmControls->GetTransform()->SetPosition(600.0f, 150.0f);
	pScene->AddGameObject(pFarmControls);
	_pFarmModeUI.emplace_back(pFarmControls);
	
	farmText = "3: Carrot   4: Demolish Plot";
	pFarmControls = new TextObject(farmText, "arial.ttf");
	pFarmControls->GetTransform()->SetPosition(700.0f, 100.0f);
	pScene->AddGameObject(pFarmControls);
	_pFarmModeUI.emplace_back(pFarmControls);

	farmText = "Buy Controls : F1: wheat seed  F2 : potato seed  F3 : Carrot Seed  F4 : sell all produce";
	pFarmControls = new TextObject(farmText, "arial.ttf");
	pFarmControls->GetTransform()->SetPosition(50.0f, 50.0f);
	pScene->AddGameObject(pFarmControls);
	_pFarmModeUI.emplace_back(pFarmControls);

	SetFarmModeUIActive(false);
}

void PlayerUIComponent::OnStart()
{
}

void PlayerUIComponent::OnUpdate()
{
}

void PlayerUIComponent::OnEnd()
{
}

void PlayerUIComponent::SetBuildModeUIActive(bool val)
{
	for (auto& obj : _pBuildModeUI) {
		obj->SetActive(val);
	}
}

void PlayerUIComponent::SetFarmModeUIActive(bool val)
{
	for (auto& obj : _pFarmModeUI) {
		obj->SetActive(val);
	}
}