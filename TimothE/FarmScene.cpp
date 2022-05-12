#include "FarmScene.h"
#include "Button.h"

void FarmScene::UpdateUI()
{
	
}

void FarmScene::UpdateObjects()
{
	Scene::UpdateObjects();

	
}

void FarmScene::InitScene()
{
	Scene::InitScene();
	
	pStartButton = new GameObject("BUTTON", ObjectType::UI);
	pStartButton->AddComponent(new Button(pStartButton));
	pStartButton->AddComponent(new BoxColliderComponent(pStartButton));
	//pStartButton->AddComponent(new TextComponent(_pTestObject));
	pStartButton->LoadTexture(ResourceManager::GetTexture("fish"));
	pStartButton->SetShader("ui");
	pStartButton->GetTransform()->SetPosition(0.0f, 0.0f);
	pStartButton->GetTransform()->SetScale({ 0.2f, 0.2f });
	pStartButton->SetType(ObjectType::UI);
	AddGameObject(pStartButton);
}
