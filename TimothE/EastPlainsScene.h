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
	void InitScene(bool hasPlayer) override;

private:


};

