#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include <iostream>
#include <thread>
#include "Window.h"

#include "Input.h"

#include <functional>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "UID.h"


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

	_pGameWindow = new Window(1280, 720, "Game");

	_pGameWindow->SetEventCallback(BIND_EVENT_FN(OnGameEvent));
	_pGameWindow->CreateWindow();

	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK)
	{
		//std::cout << "ERROR: %s", glewGetErrorString(GlewInitResult) << std::endl;
		exit(EXIT_FAILURE);
	}

	_graphics.Initialize();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ModernDarkTheme();

	if (_devMode) {
		ImGui_ImplGlfw_InitForOpenGL(_pGameWindow->GetGLFWWindow(), true);
		const char* glsl_version = "#version 330";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	ImGui::StyleColorsDark();

	_currentScene = new Scene("Test scene");

	_running = true;

	// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	float quadVertices[] = { 
	// positions   // texCoords
	-0.65f,  -0.6f,  0.0f, 0.0f,
	-0.65f,   0.82f,	0.0f, 1.0f,
	 0.6f,   0.82f,	1.0f, 1.0f,

	 0.65f,  -0.6f,  1.0f, 0.0f,
	-0.65f,  -0.6f,	0.0f, 0.0f,
	 0.6f,   0.82f,   1.0f, 1.0f
	};

	glGenVertexArrays(1, &_quadVAO);
	glGenBuffers(1, &_quadVBO);
	glBindVertexArray(_quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	_pScreenShader = new Shader("fbVert.vs", "fbFrag.fs");
	_pScreenShader->BindShader();
	int location = glGetUniformLocation(_pScreenShader->GetProgramID(), "screenTexture");
	glUniform1i(location, 0);


	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	// create a color attachment texture
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 360, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	
	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 640, 360); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Application::GameLoop()
{
	//TODO: Setup build process for game only


		//While the editor window should not close
		while (_running) {
			PollInput();

			if (_inEditorMode) {
				glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
				glEnable(GL_DEPTH_TEST);
				EditorStartRender();

				_pScreenShader->BindShader();





				EditorRender();

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glDisable(GL_DEPTH_TEST);
				glBindVertexArray(_quadVAO);
				glBindTexture(GL_TEXTURE_2D, _texture);
				glDrawArrays(GL_TRIANGLES, 0, 6);

				EditorImGUIBegin();
				//Render Here
				EditorImGUIRender();
				ImGUISwitchRender();
				EditorImGUIEndRender();


				EditorEndRender();

			

				//TODO: Replace with actual delta time
				EditorUpdate(0.016f);
			}
			else {
				GameBeginRender();

				GameRender();

				if (_devMode) {
					EditorImGUIBegin();
					ImGUISwitchRender();
					EditorImGUIEndRender();
				}

				GameEndRender();

				GameUpdate(0.016f);
			}
		}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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
	_currentScene->Update(dt);
}

void Application::EditorStartRender()
{
	_pGameWindow->SetWindowColour(0.5f, 0.5f, 0.1f, 1.0f);
}

void Application::EditorRender()
{
	
}

void Application::EditorEndRender()
{
	_pGameWindow->SwapBuffers();
}

void Application::EditorImGUIBegin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
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

void Application::EditorImGUIEndRender()
{
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	ImGui::EndFrame();
}

void Application::GameBeginRender()
{
	_pGameWindow->SetWindowColour(0.3f, 1.0f, 0.0f, 1.0f);
}

void Application::GameRender()
{
	_graphics.Render(_pGameWindow->GetGLFWWindow(), NULL);
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

void Application::ModernDarkTheme()
{
	auto& style = ImGui::GetStyle();
	style.ChildRounding = 0;
	style.GrabRounding = 0;
	style.FrameRounding = 2;
	style.PopupRounding = 0;
	style.ScrollbarRounding = 0;
	style.TabRounding = 2;
	style.WindowRounding = 0;
	style.FramePadding = { 4, 4 };

	style.WindowTitleAlign = { 0.0, 0.5 };
	style.ColorButtonPosition = ImGuiDir_Left;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = { 1.0f, 1.0f, 1.0f, 1.00f };				//
	colors[ImGuiCol_TextDisabled] = { 0.25f, 0.25f, 0.25f, 1.00f };		//
	colors[ImGuiCol_WindowBg] = { 0.2f, 0.2f, 0.2f, 1.0f };			//
	colors[ImGuiCol_ChildBg] = { 0.11f, 0.11f, 0.11f, 1.00f };			//
	colors[ImGuiCol_PopupBg] = { 0.11f, 0.11f, 0.11f, 0.94f };			//
	colors[ImGuiCol_Border] = { 0.07f, 0.08f, 0.08f, 1.00f };
	colors[ImGuiCol_BorderShadow] = { 0.00f, 0.00f, 0.00f, 0.00f };
	colors[ImGuiCol_FrameBg] = { 0.35f, 0.35f, 0.35f, 0.54f };			//
	colors[ImGuiCol_FrameBgHovered] = { 0.31f, 0.29f, 0.27f, 1.00f };
	colors[ImGuiCol_FrameBgActive] = { 0.40f, 0.36f, 0.33f, 0.67f };
	colors[ImGuiCol_TitleBg] = { 0.1f, 0.1f, 0.1f, 1.00f };
	colors[ImGuiCol_TitleBgActive] = { 0.3f, 0.3f, 0.3f, 1.00f };		//
	colors[ImGuiCol_TitleBgCollapsed] = { 0.0f, 0.0f, 0.0f, 0.61f };
	colors[ImGuiCol_MenuBarBg] = { 0.18f, 0.18f, 0.18f, 0.94f };		//
	colors[ImGuiCol_ScrollbarBg] = { 0.00f, 0.00f, 0.00f, 0.16f };
	colors[ImGuiCol_ScrollbarGrab] = { 0.24f, 0.22f, 0.21f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabHovered] = { 0.31f, 0.29f, 0.27f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabActive] = { 0.40f, 0.36f, 0.33f, 1.00f };
	colors[ImGuiCol_CheckMark] = { 0.84f, 0.84f, 0.84f, 1.0f };			//
	colors[ImGuiCol_SliderGrab] = { 0.8f, 0.8f, 0.8f, 1.0f };			//		
	colors[ImGuiCol_SliderGrabActive] = { 0.55f, 0.55f, 0.55f, 1.00f }; //
	colors[ImGuiCol_Button] = { 0.55f, 0.55f, 0.55f, 0.40f };			//
	colors[ImGuiCol_ButtonHovered] = { 0.15f, 0.15f, 0.15f, 0.62f };	//	
	colors[ImGuiCol_ButtonActive] = { 0.60f, 0.60f, 0.60f, 1.00f };		//
	colors[ImGuiCol_Header] = { 0.84f, 0.36f, 0.05f, 0.0f };			//
	colors[ImGuiCol_HeaderHovered] = { 0.25f, 0.25f, 0.25f, 0.80f };	//
	colors[ImGuiCol_HeaderActive] = { 0.42f, 0.42f, 0.42f, 1.00f };
	colors[ImGuiCol_Separator] = { 0.35f, 0.35f, 0.35f, 0.50f };		//
	colors[ImGuiCol_SeparatorHovered] = { 0.31f, 0.29f, 0.27f, 0.78f };
	colors[ImGuiCol_SeparatorActive] = { 0.40f, 0.36f, 0.33f, 1.00f };
	colors[ImGuiCol_ResizeGrip] = { 1.0f, 1.0f, 1.0f, 0.25f };			//
	colors[ImGuiCol_ResizeGripHovered] = { 1.00f, 1.0f, 1.0f, 0.4f };	//
	colors[ImGuiCol_ResizeGripActive] = { 1.00f, 1.00f, 1.0f, 0.95f };	//
	colors[ImGuiCol_Tab] = { 0.18f, 0.18f, 0.18f, 1.0f };				//
	colors[ImGuiCol_TabHovered] = { 0.58f, 0.58f, 0.58f, 0.80f };		//
	colors[ImGuiCol_TabActive] = { 0.6f, 0.60f, 0.60f, 1.00f };
	colors[ImGuiCol_TabUnfocused] = { 0.07f, 0.10f, 0.15f, 0.97f };
	colors[ImGuiCol_TabUnfocusedActive] = { 0.14f, 0.26f, 0.42f, 1.00f };
	colors[ImGuiCol_PlotLines] = { 0.66f, 0.60f, 0.52f, 1.00f };
	colors[ImGuiCol_PlotLinesHovered] = { 0.98f, 0.29f, 0.20f, 1.00f };
	colors[ImGuiCol_PlotHistogram] = { 0.60f, 0.59f, 0.10f, 1.00f };
	colors[ImGuiCol_PlotHistogramHovered] = { 0.72f, 0.73f, 0.15f, 1.00f };
	colors[ImGuiCol_TextSelectedBg] = { 0.27f, 0.52f, 0.53f, 0.35f };
	colors[ImGuiCol_DragDropTarget] = { 0.60f, 0.59f, 0.10f, 0.90f };
	colors[ImGuiCol_NavHighlight] = { 0.51f, 0.65f, 0.60f, 1.00f };
	colors[ImGuiCol_NavWindowingHighlight] = { 1.00f, 1.00f, 1.00f, 0.70f };
	colors[ImGuiCol_NavWindowingDimBg] = { 0.80f, 0.80f, 0.80f, 0.20f };
	colors[ImGuiCol_ModalWindowDimBg] = { 0.11f, 0.13f, 0.13f, 0.35f };
}
