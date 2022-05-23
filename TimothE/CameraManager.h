#pragma once
#include "Camera.h"
#include "Core/Graphics/Window.h"
#include <vector>
#include "Core.h"

class CameraManager
{
public:
	static void Init();
	CameraManager(Camera* mainCamera);
	~CameraManager();

	static Camera* MainCamera();
	static Camera* CurrentCamera();
	static void SetCamera(int cameraID); //-1 for main camera
	static void SetCamera(std::string cameraID);
	static void SetToMainCamera();
	static void RemoveCamera(int cameraID);
	static void RemoveCamera(std::string cameraID);
	static void AddCamera(Camera* newCamera);
	static void AddCamera(std::string name);
	static void ResizeCameras(float width, float height);
	
	//gets camera
	static Camera* GetCamera(int cameraID) 
	{
		if (cameraID == -1) {
			return _pMainCamera;
		}
		return _pCameras.at(cameraID); 
	}
	static Camera* GetCamera(std::string cameraID) 
	{ 
		for (int i = 0; i < _pCameras.size(); i++) {
			if (_pCameras[i]->_mName == cameraID) return _pCameras[i];
		}

		TIM_LOG_ERROR("Camera with ID: " << cameraID << " could not be found");

		return nullptr;
	}//return _pCameras.at(cameraID);


private:
	static Camera* _pMainCamera;
	static std::vector<Camera*> _pCameras;
	static Camera* _pCurrentCamera;

};



