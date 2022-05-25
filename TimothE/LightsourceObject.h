#pragma once
#include "StructureObject.h"
#include "LightLevelManager.h"
class LightsourceObject : public StructureObject
{
public:
	LightsourceObject(glm::vec2 pos, std::string name = "Light", std::string tag = "LIGHTSOURCE");

	~LightsourceObject();

	LightSource* GetLightSource() const { return _pLightSource; }


private:
	LightSource* _pLightSource;

};

