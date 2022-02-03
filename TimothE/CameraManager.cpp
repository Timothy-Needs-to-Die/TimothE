#include "CameraManager.h"

CameraManager::CameraManager(Camera* mainCamera)
{
	_pMainCamera = mainCamera;
	_pcurrentCamera = _pMainCamera;
}

CameraManager::~CameraManager()
{
	delete _pcurrentCamera;
	delete _pMainCamera;
}

void CameraManager::SetCamera(int cameraID)
{
	if (cameraID == -1)
	{
		_pcurrentCamera = _pMainCamera;
	}
	else
	{
		_pcurrentCamera = _pCameras.at(cameraID);
	}
}

void CameraManager::SetToMainCamera()
{
	_pcurrentCamera = _pMainCamera;
}

void CameraManager::RemoveCamera(int cameraID)
{
	_pCameras.erase(_pCameras.begin() +  cameraID);
}

void CameraManager::AddCamera(Camera* newCamera)
{
	_pCameras.push_back(newCamera);
}
