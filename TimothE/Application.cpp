#include <GLFW/glfw3.h>

#include "Application.h"

#include <iostream>
#include <thread>
#include "Window.h"

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
		GLFWwindow* editorWin = _pEditorWindow->GetGLFWWindow();
		std::thread editorWindowThread = std::thread([editorWin]
			{
				//While the editor window should not close
				while (!glfwWindowShouldClose(editorWin)) {
					//Sets this to be the current window being edited
					glfwMakeContextCurrent(editorWin);

					//Sets background colour and clears colour buffer bit
					glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT);

					//Swaps back and front buffer
					glfwSwapBuffers(editorWin);

					//Poll for glfw events
					glfwPollEvents();
				}

				//Terminate glfw
				glfwTerminate();
			}
		);
	}

	while (!glfwWindowShouldClose(_pGameWindow->GetGLFWWindow())) {
		//Sets this to be the current window being edited
		glfwMakeContextCurrent(_pGameWindow->GetGLFWWindow());

		//Sets background colour and clears the colour buffer bit
		glClearColor(0.3f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Swaps back and front buffer
		glfwSwapBuffers(_pGameWindow->GetGLFWWindow());

		//Poll for glfw events
		glfwPollEvents();
	}

	//Terminate glfw
	glfwTerminate();
}
