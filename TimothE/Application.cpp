#include <GLFW/glfw3.h>

#include "Application.h"

#include <iostream>
#include <thread>
#include "Window.h"

#include <functional>
#include <iostream>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

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

	_pEditorWindow->SetEventCallback(BIND_EVENT_FN(OnEditorEvent));
	_pEditorWindow->CreateWindow();
	_pGameWindow->SetEventCallback(BIND_EVENT_FN(OnGameEvent));
	_pGameWindow->CreateWindow();

	_running = true;
}

void Application::RunLoop()
{
	if (_inEditorMode) {
		//While the editor window should not close
		while (_running) {
			//Sets this to be the current window being edited
			glfwMakeContextCurrent(_pEditorWindow->GetGLFWWindow());

			//Sets background colour and clears colour buffer bit
			glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Swaps back and front buffer
			glfwSwapBuffers(_pEditorWindow->GetGLFWWindow());

			//Poll for glfw events
			glfwPollEvents();

			//==================
			//RENDER GAME WINDOW
			//==================

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
		glfwDestroyWindow(_pEditorWindow->GetGLFWWindow());
	}
	else
	{
		while (_running) {
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

	}


	//Terminate glfw
	glfwDestroyWindow(_pGameWindow->GetGLFWWindow());
}

void Application::OnEditorEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnEditorWindowClose));

	//TODO: Setup events for remaining application and input devices
}

void Application::OnGameEvent(Event& e)
{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnGameWindowClose));
}

bool Application::OnEditorWindowClose(WindowCloseEvent& e)
{
	std::cout << "Editor Window: " << e.ToString() << std::endl;
	_running = false;
	return true;
}

bool Application::OnGameWindowClose(WindowCloseEvent& e)
{
	std::cout << "Game Window: " << e.ToString() << std::endl;
	_running = false;
	return true;
}
