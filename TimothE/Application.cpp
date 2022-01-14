#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include <iostream>
#include <thread>

#include "Input.h"

#include <functional>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "UID.h"

#include "ImGuiManager.h"

#include "Texture2D.h"


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

void Application::Init(bool devMode)
{
	UID::Init();
	Input::Init();

	_pNotesBuffer = new char[16348];

	_devMode = devMode;

	if (!glfwInit()) {
		std::cout << "[ERROR: Application::Init()]: glfw failed to initialize" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	_pGameWindow = new Window(1280, 720, "TimeothE");

	_pGameWindow->SetEventCallback(BIND_EVENT_FN(OnGameEvent));
	_pGameWindow->CreateWindow();

	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK)
	{
		//std::cout << "ERROR: %s", glewGetErrorString(GlewInitResult) << std::endl;
		exit(EXIT_FAILURE);
	}

	_renderer.Initialize();

	if (_devMode) {
		ImGuiManager::CreateImGuiContext(_pGameWindow->GetGLFWWindow());
	}

	_pCurrentScene = new Scene("Test scene");

	_running = true;

	// vertex attributes for a quad that fills the editor screen space in Normalized Device Coordinates.
	float quadVertices[] = { 
	// positions   // texCoords
	-0.65f,  -0.6f,  0.0f, 0.0f,
	-0.65f,   0.82f,	0.0f, 1.0f,
	 0.6f,   0.82f,	1.0f, 1.0f,

	 0.6f,  -0.6f,  1.0f, 0.0f,
	-0.65f,  -0.6f,	0.0f, 0.0f,
	 0.6f,   0.82f,   1.0f, 1.0f
	};

	_pScreenShader = new Shader("fbVert.vs", "fbFrag.fs");
	_pEditorFramebuffer = new Framebuffer(_pScreenShader, quadVertices);
}

void Application::GameLoop()
{
	//TODO: Setup build process for game only

	double previousTime = glfwGetTime();
		//While the editor window should not close
		while (_running) {
			PollInput();

			double currentTime = glfwGetTime();
			double elapsed = currentTime - previousTime;

			if (_inEditorMode) {
				EditorStartRender();

				EditorRender();

				//Handle unbinding the editor frame buffer and drawing it's contents
				_pEditorFramebuffer->UnbindFramebuffer();
				glDisable(GL_DEPTH_TEST);
				_pEditorFramebuffer->DrawFramebuffer();

				//Render Here
				ImGuiManager::ImGuiNewFrame();
				EditorImGUIRender();
				ImGUISwitchRender();
				ImGuiManager::ImGuiEndFrame();


				EditorEndRender();

				EditorUpdate(elapsed);
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

				GameUpdate(elapsed);
			}

			previousTime = currentTime;
		}

		ImGuiManager::DestroyImGui();

	delete _pEditorFramebuffer;
	delete _pScreenShader;

	_pGameWindow->DestroyWindow();
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

void Application::EditorUpdate(float dt)
{
	_pCurrentScene->Update(dt);
}

void Application::EditorStartRender()
{
	_pEditorFramebuffer->BindFramebuffer();
	glEnable(GL_DEPTH_TEST);
	_pGameWindow->SetWindowColour(0.5f, 0.5f, 0.1f, 1.0f);
	_pEditorFramebuffer->BindShader();
}

void Application::EditorRender()
{
	
}

void Application::EditorEndRender()
{
	_pGameWindow->SwapBuffers();
}

void Application::EditorImGUIRender()
{
	{
		ImGui::Begin("Notes");

		ImGui::InputTextMultiline("Notes:", _pNotesBuffer, 16384, ImVec2(300.0f, 600.0f), 0,0, _pNotesBuffer);

		ImGui::End();
	}

	//Inspector
	{
		ImGui::Begin("Inspector");

		ImGui::End();
	}

	//Hierarchy
	{
		ImGui::Begin("Hierarchy");
		static int index = 0;
		vector<GameObject*> objects = _pCurrentScene->GetGameObjects();
		if (!objects.empty())
		{
			for (int i = 0; i < objects.size(); i++)
			{
				ImGui::RadioButton(objects[i]->GetName().c_str(), &index, i); ImGui::SameLine();
				if (ImGui::Button("Delete object"))
				{
					_pCurrentScene->RemoveGameObject(objects[i]);
					objects = _pCurrentScene->GetGameObjects();
				}
			}
			if (!objects.empty())
				GameObject* selectedObject = objects[index];
		}
		ImGui::End();
	}

	//Console
	{
		ImGui::Begin("Console");

		ImGui::End();
	}

	//Content Browser
	{
		ImGui::Begin("Content Browser");

		ImGui::End();
	}

	ImGui::ShowDemoWindow();
}

void Application::GameBeginRender()
{
	_pGameWindow->SetWindowColour(0.3f, 1.0f, 0.0f, 1.0f);
}

void Application::GameRender()
{
	_pCurrentScene->RenderScene(&_renderer);
}

void Application::GameEndRender()
{
	_pGameWindow->SwapBuffers();
}

void Application::GameUpdate(float dt)
{

}

void Application::ImGUISwitchRender()
{
	{
		ImGui::Begin("Application Mode");
		
		if (ImGui::Button("Editor", ImVec2(100.0f, 30.0f))) {
			_inEditorMode = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Game", ImVec2(100.0f, 30.0f))) {
			_inEditorMode = false;
		}
		ImGui::SameLine();
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