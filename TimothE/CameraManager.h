#pragma once
#include "Camera.h"
#include <vector>

static class CameraManager
{
public:
	Camera* _pMainCamera;
	std::vector<Camera*> _pCameras;
	Camera* _pcurrentCamera;

	CameraManager(Camera* mainCamera);
	~CameraManager();
	void SetCamera(int cameraID); //-1 for main camera
	void SetCamera(std::string cameraID);
	void SetToMainCamera();
	void RemoveCamera(int cameraID);
	void RemoveCamera(std::string cameraID);
	void AddCamera(Camera* newCamera);
	//gets camera
	Camera* GetCamera(int cameraID) { return _pCameras.at(cameraID); }
	Camera* GetCamera(std::string cameraID) { }//return _pCameras.at(cameraID);
};



