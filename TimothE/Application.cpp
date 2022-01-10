#include "Application.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>

void Application::Init(bool createEditorWindow)
{
	_inEditorMode = createEditorWindow;

	if (!glfwInit()) {
		std::cout << "[ERROR: Application::Init()]: glfw failed to initialize" << std::endl;
	}

	_pGameWindow = new Window(1280, 720, "Game");

	if (createEditorWindow) {
		_pEditorWindow = new Window(1280, 720, "TimothE Engine");
	}
}

void Application::RunLoop()
{
	if (_inEditorMode) {
		std::thread editorThread = std::thread([_pEditorWindow] 
			{
				
			});
	}
}
