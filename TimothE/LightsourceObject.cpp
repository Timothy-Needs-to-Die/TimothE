#include "pch.h"
#include "LightsourceObject.h"
#include "FarmScene.h"

LightsourceObject::LightsourceObject(glm::vec2 pos, std::string name, std::string tag /*= "LIGHTSOURCE"*/)
	: StructureObject(name, tag)
{
	_pLightSource = new LightSource();

	_pTransform->SetPosition(pos);
	_pLightSource->worldPos = pos;

	//TODO: Change this. Shouldn't be referencing the farm scene and should be generalised
	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());

	if (pFarmScene) {
		LightLevelManager* pLightManager = pFarmScene->GetLightManager();

		pLightManager->AddLightSource(_pLightSource);
	}
}

LightsourceObject::~LightsourceObject()
{
	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());

	if (pFarmScene) {
		LightLevelManager* pLightManager = pFarmScene->GetLightManager();

		pLightManager->RemoveLightSource(_pLightSource);
	}
}
