#include "Application.h"
#include "Input.h"
#include "imgui.h"
#include "UID.h"
#include "ImGuiManager.h"
#include "Texture2D.h"
#include "SubTexture2D.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Editor.h"
#include "Renderer2D.h"
#include "TileMap.h"

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

//initializes application
void Application::Init(bool devMode)
{
	UID::Init();
	Input::Init();
	HeapManager::Init();

	_mDevMode = devMode;

	//checks if glfw initialsed
	if (!glfwInit()) {
		std::cout << "[ERROR: Application::Init()]: glfw failed to initialize" << std::endl;
	}

	//sets up new window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	Window::Init(1920, 1080, "ThymeoWthE");

	Window::SetEventCallback(BIND_EVENT_FN(OnGameEvent));
	Window::CreateWindow();

	//checks glew initialises
	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK)
	{
		//std::cout << "ERROR: %s", glewGetErrorString(GlewInitResult) << std::endl;
		exit(EXIT_FAILURE);
	}

	//enables debug messages
	GLCall(glEnable(GL_DEBUG_OUTPUT));
	//GLCall(glDebugMessageCallback(MessageCallback, 0));

	if (_mDevMode) {
		ImGuiManager::CreateImGuiContext(Window::GetGLFWWindow());
	}

	//initializes resource manager
	ResourceManager::Init();

	Renderer2D::Init();

	//initializes editor with scene
	_pCurrentScene = new Scene("Test scene");
	_pEditor = new Editor(this);
	_mRunning = true;

	float aspectRatio = Window::GetAspectRatio();
	float zoomLevel = 1.0f;
	float left = -aspectRatio * zoomLevel;
	float right = aspectRatio * zoomLevel;
	float bottom = -zoomLevel;
	float top = zoomLevel;
	_pGameCamera = new Camera(left, right, bottom, top);
	_pGameCamera->SetCameraSpeed(2.5f);

	_pTilemap = new TileMap();
	//Layer, X sprite index, y sprite index, index for placement
}

//game loop update
void Application::GameLoop()
{
	//TODO: Setup build process for game only

	//Intial mem bookmark
	int memBookmark = HeapManager::GetMemoryBookmark();

	//creates new audio engine
	_pAudio = new AudioEngine;

	//enables depth in opengl
	GLCall(glEnable(GL_DEPTH_TEST));

	//time update
	double previousTime = glfwGetTime();

	//SoundStruct TitleSong = _audio->LoadSound("Title Song", "Resources/Sounds/Music/Title.wav", Type_Song);


	//While the editor window should not close
	while (_mRunning) {
		PollInput();

		//plays sounds
		//if (STstarted == false)
		//{
		//	//_audio->PlaySong(TitleSong);
		//	STstarted = true;
		//}

		//deltatime update
		double deltaTime = glfwGetTime();
		double elapsed = deltaTime - previousTime;

		//imgui update frame
		ImGuiManager::ImGuiNewFrame();

		_pTilemap->UpdateLogic(_pEditor->GetCamera());

		//update editor if in editor mode
		if (_mInEditorMode) {
			_pEditor->_pEditorFramebuffer->BindFramebuffer();
			GameBeginRender();

			GameRender(_pEditor->GetCamera());
			_pEditor->EditorLoop(_pCurrentScene, elapsed, _mInEditorMode, _mPaused);

			if (Input::IsMouseButtonDown(BUTTON_LEFT)) {
				_pTilemap->AddTileAt(0, 3, 5, _pEditor->GetCamera());
			}

			//_pEditor->GetCamera()->PrintInfo();

			_pEditor->_pEditorFramebuffer->UnbindFramebuffer();

			_pEditor->EditorRender();
		}
		//update game if in game mode
		else {
			GameBeginRender();

			GameRender(_pGameCamera);

			//_pGameCamera->PrintInfo();

			if (_mGameRunning && !_mPaused) {
				GameUpdate(elapsed);
			}

			if (_mDevMode) {
				ImGUISwitchRender();
			}
		}

		ImGuiManager::ImGuiEndFrame();

		Window::SwapBuffers();

		previousTime = deltaTime;
	}

	//saves scene
	_pCurrentScene->SaveScene("scene1.scene");

	//delete
	ImGuiManager::DestroyImGui();
	delete _pEditor;
	Window::DestroyWindow();

	//Prints the memory status and reports and memory leaks
	//HeapManager::ReportMemoryLeaks(memBookmark);
}

//run events
void Application::OnGameEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressedEvent));
	dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleasedEvent));
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMovedEvent));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolledEvent));
}

//on game start start game state
void Application::GameStart()
{
	_pCurrentScene->SceneStart();
	_mInEditorMode = false;
	_mPaused = false;
	_mGameRunning = true;
}

//polls input
void Application::PollInput()
{
	glfwPollEvents();
}

//clears and adds background
void Application::GameBeginRender()
{
	Window::SetWindowColour(0.3f, 1.0f, 0.0f, 1.0f);
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

//render game
void Application::GameRender(Camera* cam)
{
	_pTilemap->RenderMap(cam);
	_pCurrentScene->RenderScene(cam);
}

//updates game scene
void Application::GameUpdate(float dt)
{
	_pGameCamera->Update(dt);
	_pCurrentScene->Update(dt);
}

//stop and play buttons switches play states
void Application::ImGUISwitchRender()
{
	{
		//sets up window for application mode
		ImGui::Begin("#Application Mode", 0, ImGuiWindowFlags_AlwaysAutoResize);
		//stop playing button changes game back to editor mode
		if (ImGui::Button("Stop Playing", ImVec2(100.0f, 30.0f))) {
			_mInEditorMode = true;
			_mGameRunning = false;
			_mPaused = false;
		}
		ImGui::SameLine();
		//unpauses game
		if (_mPaused) {
			if (ImGui::Button("Resume", ImVec2(90.0f, 30.0f)))
			{
				_mPaused = false;
			}
		}
		ImGui::SameLine();

		//pause button
		if (ImGui::Button("Pause", ImVec2(90.0f, 30.0f)))
		{
			_mPaused = true;
		}
		ImGui::SameLine();
		ImGui::End();
	}
}

//closes game window
bool Application::OnWindowClose(WindowCloseEvent& e)
{
	std::cout << "Game Window: " << e.ToString() << std::endl;
	_mRunning = false;
	return true;
}

//input event for given input
bool Application::OnKeyPressedEvent(KeyPressedEvent& e)
{
	//1: Is marked as GLFW repeat value
	if (e.GetRepeatCount() == 1) {
		Input::SetKey((TimothEKeyCode)e.GetKeyCode(), HELD);
	}
	//else for button pressed quickly
	else
	{
		Input::SetKey((TimothEKeyCode)e.GetKeyCode(), PRESSED);
	}

	return true;
}

//when key is released return true
bool Application::OnKeyReleasedEvent(KeyReleasedEvent& e)
{
	Input::SetKey((TimothEKeyCode)e.GetKeyCode(), RELEASE);
	return true;
}

//when key is pressed return true
bool Application::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	Input::SetMouseButton((TimothEMouseCode)e.GetMouseButton(), PRESSED);
	return true;
}

//when mouse button is released return true
bool Application::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	Input::SetMouseButton((TimothEMouseCode)e.GetMouseButton(), RELEASE);
	return true;
}

//if mouse is moved return false
bool Application::OnMouseMovedEvent(MouseMovedEvent& e)
{
	float mouseY = e.GetY();

	mouseY = Window::GetHeight() - mouseY;

	Input::SetMousePosition(e.GetX(), mouseY);
	return true;
}

bool Application::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
	_pEditor->GetCamera()->OnMouseScrolled(e.GetOffsetY());

	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	_pGameCamera->OnResize((float)e.GetWidth(), (float)e.GetHeight());
	_pEditor->GetCamera()->OnResize((float)e.GetWidth(), (float)e.GetHeight());

	return true;
}
