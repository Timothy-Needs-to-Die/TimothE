#pragma once
#include "Camera.h"
#include <vector>

class CameraManager
{
public:
	Camera* _pMainCamera;
	std::vector<Camera*> cameras;
	Camera* currentCamera;

	CameraManager();
	~CameraManager();
	//Camera GetCamera() {return };

private:
};

