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
}