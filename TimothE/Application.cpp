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
#include "Button.h"
#include "ResourceManager.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

void GLAPIENTRY MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

void Application::Init(bool devMode)
{
	UID::Init();
	Input::Init();
	HeapManager::Init();
	ResourceManager::Init();

	InitResources();

	_devMode = devMode;

	_renderer = new Renderer();

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

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

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

	//_pCurrentScene->LoadScene("scene1.scene");

	glEnable(GL_DEPTH_TEST);

	double previousTime = glfwGetTime();
	bool STstarted = false;

	SoundStruct TitleSong = _audio->LoadSound("Title Song", "Resources/Sounds/Music/Title.wav", Type_Song);

	Camera* _pGameCamera = new Camera(_pWindow->GetGLFWWindow(), 1280, 720, 45.0f);

	//While the editor window should not close
	while (_running) {
		PollInput();

		if (STstarted == false)
		{
			//_audio->PlaySong(TitleSong);
			STstarted = true;

		}

		double currentTime = glfwGetTime();
		double elapsed = currentTime - previousTime;

		_pGameCamera->Update(elapsed);

		ImGuiManager::ImGuiNewFrame();

		if (_inEditorMode) {
			_pEditor->_pEditorFramebuffer->BindFramebuffer();
			GameBeginRender();
			glEnable(GL_DEPTH_TEST);


			GameRender();

			if(!_paused)
				GameUpdate(elapsed);

			_pEditor->_pEditorFramebuffer->UnbindFramebuffer();
			glDisable(GL_DEPTH_TEST);

			glClear(GL_COLOR_BUFFER_BIT);
			_pEditor->EditorRender();
			_pEditor->EditorLoop(_pCurrentScene, elapsed, _inEditorMode, _paused);
		}
		else {
			GameBeginRender();
			glEnable(GL_DEPTH_TEST);

			GameRender();

			if (_devMode) {
				ImGUISwitchRender();
			}

			if (!_paused)
				GameUpdate(elapsed);

			glDisable(GL_DEPTH_TEST);
		}
		ImGuiManager::ImGuiEndFrame();

		_pWindow->SwapBuffers();

		previousTime = currentTime;
	}
	_pCurrentScene->SaveScene("scene1.scene");

	ImGuiManager::DestroyImGui();
	delete _pEditor;
	_pWindow->DestroyWindow();

	//Prints the memory status and reports and memory leaks
	HeapManager::ReportMemoryLeaks(memBookmark);

}


void Application::OnGameEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnGameWindowClose));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnGameWindowKeyPressedEvent));
	dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnGameWindowKeyReleasedEvent));
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnGameWindowMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnGameWindowMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnGameWindowMouseMovedEvent));
}

void Application::PollInput()
{
	glfwPollEvents();
}

void Application::GameBeginRender()
{
	_pWindow->SetWindowColour(0.3f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::GameRender()
{
	_pCurrentScene->RenderScene(_renderer);
}

void Application::GameEndRender()
{
	_pWindow->SwapBuffers();
}

void Application::GameUpdate(float dt)
{
	_pCurrentScene->Update(dt);
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

bool Application::OnGameWindowMouseMovedEvent(MouseMovedEvent& e)
{
	float mouseY = e.GetY();

	mouseY = _pWindow->GetHeight() - mouseY;

	Input::SetMousePosition(e.GetX(), mouseY);
	return false;
}

void Application::InitResources()
{
	//INITIALIZE ALL RESOURCES HERE
	ResourceManager::InstantiateTexture("lenna3", "lenna3.jpg");
}
