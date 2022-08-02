#pragma once
#include "Scene.h"


class EastPlainsScene : public Scene
{
public:
	EastPlainsScene(std::string name) : Scene(name)
	{
	}

	~EastPlainsScene();

	void UpdateUI() override;
	void UpdateObjects() override;
	void InitScene() override;

private:
	class Player* _pPlayer = nullptr;


};

