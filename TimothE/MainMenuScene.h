#pragma once
#include "Scene.h"

class MainMenuScene :
    public Scene
{
public:

	MainMenuScene(std::string name) : Scene(name)
	{

	}

	~MainMenuScene();

	void UpdateUI() override;
	void UpdateObjects() override;
	void InitScene() override;
private:

	class GameTimeManager* _pGameTime = nullptr;
	class MainMenuUI* _pMainMenuUI = nullptr;
};

