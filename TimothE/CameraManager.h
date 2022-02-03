#pragma once
#include "Camera.h"
#include <vector>

class CameraManager
{
public:
	Camera* _pMainCamera;
	std::vector<Camera*> _pCameras;
	Camera* _pcurrentCamera;

	CameraManager(Camera* mainCamera);
	~CameraManager();
	void SetCamera(int cameraID); //-1 for main camera
	void SetToMainCamera();
	void RemoveCamera(int cameraID);
	void AddCamera(Camera* newCamera);
	//Camera GetCamera() {return };

private:
};

