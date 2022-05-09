#pragma once
#include "Scene.h"
class FarmScene : public Scene
{
public:

	FarmScene(std::string name) : Scene(name)
	{

	}

	void UpdateUI() override;
	void UpdateObjects() override;
	void InitScene() override;

protected:


private:
	GameObject* pStartButton = nullptr;
};

