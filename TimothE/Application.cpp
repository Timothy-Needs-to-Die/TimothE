#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include <iostream>
#include <thread>

#include "Input.h"

#include <functional>
#include <iostream>

#include "imgui.h"

#include "UID.h"

#include "ImGuiManager.h"

#include "Texture2D.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

void Application::Init(bool devMode)
{
	UID::Init();
	Input::Init();
	Renderer::Initialize();
	HeapManager::Init();

	_devMode = devMode;

	if (!glfwInit()) {
		std::cout << "[ERROR: Application::Init()]: glfw failed to initialize" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	_pWindow = new Window(1280, 720, "ThymeoWthE");

	_pWindow->SetEventCallback(BIND_EVENT_FN(OnGameEvent));
	_pWindow->CreateWindow();

	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK)
	{
		//std::cout << "ERROR: %s", glewGetErrorString(GlewInitResult) << std::endl;
		exit(EXIT_FAILURE);
	}

	if (_devMode) {
		ImGuiManager::CreateImGuiContext(_pWindow->GetGLFWWindow());
	}

	_pCurrentScene = new Scene("Test scene");
	_pEditor = new Editor(_pWindow);
	_running = true;
}

void Application::GameLoop()
{
	//TODO: Setup build process for game only

	//Intial mem bookmark
	int memBookmark = HeapManager::GetMemoryBookmark();

	_audio = new AudioEngine;

	_pCurrentScene->LoadScene("scene1.scene");


	double previousTime = glfwGetTime();
	bool STstarted = false;

	SoundStruct TitleSong = _audio->LoadSound("Title Song", "Resources/Sounds/Music/Title.wav", Type_Song);
	
	

	//While the editor window should not close
	while (_running) {
		PollInput();
		
		if (STstarted == false)
		{
			_audio->PlaySong(TitleSong);
			STstarted = true;

		}

		double currentTime = glfwGetTime();
		double elapsed = currentTime - previousTime;

		if (_inEditorMode) {
			_pEditor->EditorLoop(_pCurrentScene, elapsed, _inEditorMode, _paused);
		}
		else {
			GameBeginRender();

			GameRender();

			if (_devMode) {
				ImGuiManager::ImGuiNewFrame();
				ImGUISwitchRender();
				ImGuiManager::ImGuiEndFrame();
			}

			GameEndRender();

			if(!_paused)
				GameUpdate(elapsed);
		}

		previousTime = currentTime;
	}

	ImGuiManager::DestroyImGui();
	delete _pEditor;
	_pWindow->DestroyWindow();

	//Prints the memory status and reports and memory leaks
	HeapManager::ReportMemoryLeaks(memBookmark);

	_pCurrentScene->SaveScene("scene1.scene");
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

void Application::PollInput()
{
	glfwPollEvents();
}

void Application::GameBeginRender()
{
	_pWindow->SetWindowColour(0.3f, 1.0f, 0.0f, 1.0f);
}

void Application::GameRender()
{
	_pCurrentScene->RenderScene(&_renderer);
}

void Application::GameEndRender()
{
	_pWindow->SwapBuffers();
}

void Application::GameUpdate(float dt)
{

}

void Application::ImGUISwitchRender()
{
	{
		ImGui::Begin("#Application Mode");

		if (ImGui::Button("Editor", ImVec2(100.0f, 30.0f))) {
			_inEditorMode = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Game", ImVec2(100.0f, 30.0f))) {
			_inEditorMode = false;
		}
		ImGui::SameLine();
		//float width = ImGui::GetWindowSize().x;
		//ImGui::SetCursorPosX((width - 30.0f) * 0.5f); // sets play and pause button to centre of window
		if (ImGui::Button("Play", ImVec2(50.0f, 30.0f)))
		{
			_paused = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause", ImVec2(50.0f, 30.0f)))
		{
			_paused = true;
		}
		ImGui::SameLine();
		//resets game build
		if (ImGui::Button("Stop", ImVec2(50.0f, 30.0f)))
		{
			_pCurrentScene = new Scene("Test scene");
			_paused = true;
		}
		ImGui::SameLine();
		ImGui::Text(("Paused: " + to_string(_paused)).c_str());
		ImGui::End();
	}
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
