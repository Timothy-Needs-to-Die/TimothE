#include <GLFW/glfw3.h>

#include "Application.h"

#include <iostream>
#include <thread>
#include "Window.h"

#include "Input.h"

#include <functional>
#include <iostream>

#include "UID.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

void Application::Init(bool createEditorWindow)
{
	UID::Init();

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

	Input::Init();
	

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

			//INPUT TEST CODE
			//if (Input::IsKeyDown(KEY_W)) {
			//	std::cout << "W is Pressed" << std::endl;
			//}
			//
			//if (Input::IsKeyHeld(KEY_W)) {
			//	std::cout << "W is Held" << std::endl;
			//}
			//
			//if (Input::IsKeyUp(KEY_W)) {
			//	std::cout << "W is Up" << std::endl;
			//}
			//
			//if (Input::IsMouseButtonDown(BUTTON_LEFT)) {
			//	std::cout << "Left Mouse Button is down" << std::endl;
			//}
			//
			//if (Input::IsMouseButtonUp(BUTTON_LEFT)) {
			//	std::cout << "Left Mouse Button is up" << std::endl;
			//}
			//END OF INPUT TEST CODE

			//Unique ID test
			//std::cout << UID::GenerateUID() << std::endl;

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
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnEditorWindowKeyPressedEvent));
	dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnEditorWindowKeyReleasedEvent));
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnEditorWindowMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnEditorWindowMouseButtonReleasedEvent));

	//TODO: Setup events for remaining application and input devices
}

void Application::OnGameEvent(Event& e)
{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnGameWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnGameWindowKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnGameWindowKeyReleasedEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnGameWindowMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnGameWindowMouseButtonReleasedEvent));
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

bool Application::OnGameWindowKeyPressedEvent(KeyPressedEvent& e)
{
	//1: Is marked as GLFW repeat value
	if (e.GetRepeatCount() == 1) {
		Input::SetKey((TimothEKeyCode)e.GetKeyCode(), HELD);
	}
	else
	{
		Input::SetKey((TimothEKeyCode)e.GetKeyCode(), PRESSED);
	}

	return true;
}

bool Application::OnGameWindowKeyReleasedEvent(KeyReleasedEvent& e)
{
	Input::SetKey((TimothEKeyCode)e.GetKeyCode(), RELEASE);
	return true;
}


bool Application::OnGameWindowMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	Input::SetMouseButton((TimothEMouseCode)e.GetMouseButton(), PRESSED);
	return true;
}

bool Application::OnGameWindowMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	Input::SetMouseButton((TimothEMouseCode)e.GetMouseButton(), RELEASE);
	return true;
}

bool Application::OnEditorWindowKeyPressedEvent(KeyPressedEvent& e)
{
	//1: Is marked as GLFW repeat value
	if (e.GetRepeatCount() == 1) {
		Input::SetKey((TimothEKeyCode)e.GetKeyCode(), HELD);
	}
	else
	{
		Input::SetKey((TimothEKeyCode)e.GetKeyCode(), PRESSED);
	}

	return true;
}

bool Application::OnEditorWindowKeyReleasedEvent(KeyReleasedEvent& e)
{
	Input::SetKey((TimothEKeyCode)e.GetKeyCode(), RELEASE);
	return true;
}

bool Application::OnEditorWindowMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	Input::SetMouseButton((TimothEMouseCode)e.GetMouseButton(), PRESSED);
	return true;
}

bool Application::OnEditorWindowMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	Input::SetMouseButton((TimothEMouseCode)e.GetMouseButton(), RELEASE);
	return true;
}
