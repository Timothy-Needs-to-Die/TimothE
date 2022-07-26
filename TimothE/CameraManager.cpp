#include "pch.h"
#include "CameraManager.h"

void CameraManager::Init()
{
	float aspectRatio = Window::GetAspectRatio();
	float zoomLevel = 2.0f;
	float left = -aspectRatio * zoomLevel;
	float right = aspectRatio * zoomLevel;
	float bottom = -zoomLevel;
	float top = zoomLevel;
	_pMainCamera = std::make_shared<Camera>(left, right, bottom, top, aspectRatio, "Main Camera");
}

CameraManager::CameraManager(std::shared_ptr<Camera> mainCamera)
{
	_pMainCamera = mainCamera;
	_pCurrentCamera = _pMainCamera;
}

CameraManager::~CameraManager()
{
	
}

std::shared_ptr<Camera> CameraManager::MainCamera()
{
	return _pMainCamera;
}

std::shared_ptr<Camera> CameraManager::CurrentCamera()
{
	return _pCurrentCamera;
}

//sets camera with id (-1 for main camera)
void CameraManager::SetCamera(int cameraID)
{
	if (cameraID == -1)
	{
		_pCurrentCamera = _pMainCamera;
	}
	else
	{
		_pCurrentCamera = _pCameras.at(cameraID);
	}
}

void CameraManager::SetCamera(std::string cameraID)
{
	if (cameraID == "Main Camera")
	{
		_pCurrentCamera = _pMainCamera;
	}
	for (int i = 0; i < _pCameras.size(); i++)
	{
		if (_pCameras[i]->GetName() == cameraID)
		{
			_pCurrentCamera = _pCameras[i];
			break;
		}
	}
}

//sets to main camera
void CameraManager::SetToMainCamera()
{
	_pCurrentCamera = _pMainCamera;
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
		if (_pCameras[i]->GetName() == cameraID)
		{
			_pCameras.erase(_pCameras.begin() + i);
			break;
		}
	}
}

//adds new camera
void CameraManager::AddCamera(std::shared_ptr<Camera> newCamera)
{
	_pCameras.push_back(newCamera);
}

void CameraManager::AddCamera(std::string name)
{
	float aspectRatio = Window::GetAspectRatio();
	float zoomLevel = 2.0f;
	float left = -aspectRatio * zoomLevel;
	float right = aspectRatio * zoomLevel;
	float bottom = -zoomLevel;
	float top = zoomLevel;
	std::shared_ptr<Camera> nc = std::make_shared<Camera>(left, right, bottom, top, Window::GetAspectRatio(), name);
	_pCameras.push_back(nc);
}

void CameraManager::ResizeCameras(float width, float height)
{
	_pMainCamera->OnResize(width, height);
	for (int i = 0; i < _pCameras.size(); i++) {
		_pCameras[i]->OnResize(width, height);
	}
}

std::shared_ptr<Camera> CameraManager::_pMainCamera;
std::vector<std::shared_ptr<Camera>> CameraManager::_pCameras;
std::shared_ptr<Camera> CameraManager::_pCurrentCamera;
