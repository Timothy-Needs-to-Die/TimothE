#include "pch.h"
#include "Application.h"
#include "Input.h"
#include "imgui.h"
#include "UID.h"
#include "ImGuiManager.h"
#include "Texture2D.h"
#include "Core/Graphics/SubTexture2D.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Editor.h"
#include "Core/Graphics/Renderer2D.h"
#include "TileMap.h"
#include "Time.h"
#include "FarmScene.h"
#include "CSVReader.h"
#include "CropConfig.h"
#include "Core.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

double Time::_deltaTime;
double Time::_time;

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
		TIM_LOG_ERROR("glfw failed to initialize");
	}


	//sets up new window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_AUTO_ICONIFY, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);


	Window::Init(1280, 720, "ThymeoWthE");

	Window::SetEventCallback(BIND_EVENT_FN(OnGameEvent));
	Window::CreateWindow();

	//checks glew initialises
	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK)
	{
		std::cout << "ERROR: %s" << glewGetErrorString(GlewInitResult) << std::endl;
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

	Scene* pScene = SceneManager::CreateScene(ResourceManager::GetScene("MainMenuScene"));
	pScene->SetHasTilemap(false);

	SceneManager::SetCurrentScene(pScene);
	//SceneManager::SetCurrentScene(SceneManager::CreateScene(ResourceManager::GetScene("TownScene")));
	

	//initializes editor with scene

	_mRunning = true;

	CameraManager::Init();
	CameraManager::MainCamera()->SetCameraSpeed(2.0f);

	CameraManager::AddCamera("Editor");
	CameraManager::GetCamera("Editor")->SetPosition({ 1.78f, 1.0f, -1.0f });
	CameraManager::SetToMainCamera();

	_pfb = new Framebuffer(ResourceManager::GetShader("framebuffer"));

	_pEditor = new Editor(this);
	//_pCameraManager->_pCameras = _pCurrentScene->FindObjectsOfType<Camera>();
}

//game loop update
void Application::GameLoop()
{
	//TODO: Setup build process for game only

	//Intial mem bookmark
	int memBookmark = HeapManager::GetMemoryBookmark();

	//creates new audio engine
	_pAudio = new AudioEngine();


	//time update
	double previousTime = glfwGetTime();

	//SoundStruct TitleSong = _audio->LoadSound("Title Song", "Resources/Sounds/Music/Title.wav", Type_Song);

	//_pCurrentScene->LoadScene("scene1.scene");

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

		Time::Update(deltaTime - previousTime , glfwGetTime());

		//imgui update frame
		ImGuiManager::ImGuiNewFrame();

		//_pTilemap->UpdateLogic(CameraManager::GetCamera("Editor"));

		if (DEV_MODE) {
			if (Input::IsKeyDown(TimothEKeyCode::KEY_0)) {
				_tileMapEditorEnabled = !_tileMapEditorEnabled;
				TileMapEditor::_active = _tileMapEditorEnabled;
				std::string cameraName = _tileMapEditorEnabled ? "Editor" : "Main Camera";
				CameraManager::SetCamera(cameraName);
			}
		}


		if (_tileMapEditorEnabled) {
			_pEditor->_pEditorFramebuffer->BindFramebuffer();
			GameBeginRender();
			GameRender(CameraManager::GetCamera("Editor"));
			_pEditor->EditorLoop(SceneManager::GetCurrentScene(), _tileMapEditorEnabled, _mPaused);

			_pEditor->_pEditorFramebuffer->UnbindFramebuffer();
			_pEditor->EditorRender();
		}
		else {

			_pfb->BindFramebuffer();
			GameBeginRender();
			GameRender(CameraManager::MainCamera());
			GameUpdate();
			_pfb->UnbindFramebuffer();
			
			_pfb->DrawFramebuffer();
		}




		ImGuiManager::ImGuiEndFrame();

		Window::SwapBuffers();
		Window::ShowFPS(Time::GetDeltaTime());

		previousTime = deltaTime;

		SceneManager::GetCurrentScene()->FrameEnd();
	}

	//saves scene
	//_pCurrentScene->SaveScene("Resources/Scenes/" + _pCurrentScene->GetName() + ".scene");

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
	dispatcher.Dispatch<WindowFocusedEvent>(BIND_EVENT_FN(OnWindowFocusEvent));
}

//on game start start game state
void Application::GameStart()
{
	SceneManager::GetCurrentScene()->SceneStart();
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
	//Benji did this because they're an amazing programmer/genius.
	//Window::SetWindowColour(0.553f, 0.768f, 0.207f, 1.0f);
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

//render game
void Application::GameRender(Camera* cam)
{
	//_pTilemap->RenderMap(cam);
	SceneManager::GetCurrentScene()->RenderScene(cam);
}

//updates game scene
void Application::GameUpdate()
{
	CameraManager::CurrentCamera()->OnUpdate();
	SceneManager::GetCurrentScene()->Update();
}

void Application::DisplayTileEditor()
{
	TileMapEditor::Update(SceneManager::GetCurrentScene()->GetTileMap());
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
	float mouseX = e.GetX();

	mouseY = Window::GetHeight() - mouseY;

	mouseY /= Window::GetHeight();
	mouseX /= Window::GetWidth();

	mouseY -= 1.0f;
	mouseY *= 2.0f;
	mouseY += 1.0f;

	mouseX -= 1.0f;
	mouseX *= 2.0f;
	mouseX += 1.0f;

	//std::cout << "Mouse (" << mouseX << ", " << mouseY << ")" << std::endl;

	Input::SetMousePosition(mouseX, mouseY);
	return true;
}

bool Application::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
	//TODO: Only allow this when hovered over the window
	//CameraManager::GetCamera("Editor")->OnMouseScrolled(e.GetOffsetY());

	return true;
}


bool Application::OnWindowFocusEvent(WindowFocusedEvent& e)
{
	std::cout << e.ToString() << std::endl;
	
	if (e.IsFocused()) {
		glfwFocusWindow(Window::GetGLFWWindow());
		CameraManager::ResizeCameras(Window::GetWidth(), Window::GetHeight());
		CameraManager::MainCamera()->SetPosition({ 1.78f, 1.0f, -2.0f });
		CameraManager::MainCamera()->RecalculateViewMatrix();
	}

	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	CameraManager::ResizeCameras((float)e.GetWidth(), (float)e.GetHeight());
	glViewport(0, 0, e.GetWidth(), e.GetHeight());
	_pfb->RefreshTexture();
	_pfb->RefreshRBO();

	_pEditor->_pEditorFramebuffer->RefreshTexture();
	_pEditor->_pEditorFramebuffer->RefreshRBO();
	return true;
}
