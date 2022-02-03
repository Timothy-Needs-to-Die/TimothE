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

//sets camera with id (-1 for main camera)
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

void CameraManager::SetCamera(std::string cameraID)
{
	if (cameraID == "Main Camera")
	{
		_pcurrentCamera = _pMainCamera;
	}
	for (int i = 0; i < _pCameras.size(); i++)
	{
		if (_pCameras[i]->_mName == cameraID)
		{
			_pcurrentCamera = _pCameras[i];
			break;
		}
	}
}

//sets to main camera
void CameraManager::SetToMainCamera()
{
	_pcurrentCamera = _pMainCamera;
}

//removes camera at position
void CameraManager::RemoveCamera(int cameraID)
{
	_pCameras.erase(_pCameras.begin() +  cameraID);
}

void CameraManager::RemoveCamera(std::string cameraID)
{
	for (int i = 0; i < _pCameras.size(); i++)
	{
		if (_pCameras[i]->_mName == cameraID)
		{
			_pCameras.erase(_pCameras.begin() + i);
			break;
		}
	}
}

//adds new camera
void CameraManager::AddCamera(Camera* newCamera)
{
	_pCameras.push_back(newCamera);
}
