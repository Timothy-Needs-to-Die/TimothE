#pragma once
#include "Scene.h"
class TownScene :
    public Scene
{
public: 
    TownScene(std::string name) : Scene(name) {

    }

    void UpdateUI() override;
    void UpdateObjects() override;
    void InitScene() override;

private:

};

