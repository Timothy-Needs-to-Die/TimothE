#pragma once
#include "GameObject.h"
#include <string>
class MainMenuUI :
    public GameObject
{

public:
    MainMenuUI(std::string name = "MainMenuUI", std::string tag = "UNTAGGED");
private:
    GameObject* _pPressToPlay = nullptr;
    GameObject* _pTitle = nullptr;
    GameObject* _pLogo = nullptr;
    GameObject* _pMadeBy = nullptr;
};

