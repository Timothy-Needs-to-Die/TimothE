#pragma once
#include "Camera.h"
#include "Core/Graphics/Window.h"
#include <vector>
#include "Core.h"

class CameraManager
{
public:
	static void Init();
	CameraManager(std::shared_ptr<Camera> mainCamera);
	~CameraManager();

	static std::shared_ptr<Camera> MainCamera();
	static std::shared_ptr<Camera> CurrentCamera();
	static void SetCamera(int cameraID); //-1 for main camera
	static void SetCamera(std::string cameraID);
	static void SetToMainCamera();
	static void RemoveCamera(int cameraID);
	static void RemoveCamera(std::string cameraID);
	static void AddCamera(std::shared_ptr<Camera> newCamera);
	static void AddCamera(std::string name);
	static void ResizeCameras(float width, float height);
	
	//gets camera
	static std::shared_ptr<Camera> GetCamera(int cameraID)
	{
		if (cameraID == -1) {
			return _pMainCamera;
		}
		return _pCameras.at(cameraID); 
	}
	static std::shared_ptr<Camera> GetCamera(std::string cameraID)
	{ 
		for (int i = 0; i < _pCameras.size(); i++) {
			if (_pCameras[i]->GetName() == cameraID) return _pCameras[i];
		}

		TIM_LOG_ERROR("Camera with ID: " << cameraID << " could not be found");

		return nullptr;
	}


private:
	static std::shared_ptr<Camera> _pMainCamera;
	static std::vector<std::shared_ptr<Camera>> _pCameras;
	static std::shared_ptr<Camera> _pCurrentCamera;

};



