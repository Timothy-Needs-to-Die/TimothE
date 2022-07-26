﻿#include "pch.h"
#include "Editor.h"
#include "ImGuiManager.h"
#include "Texture2D.h"
#include "BoxColliderComponent.h"

#include "misc/cpp/imgui_stdlib.h"
#include "misc/cpp/imgui_stdlib.cpp"
#include "dirent.h"
#include "Input.h"
#include "Application.h"
#include "imgui.h"
//#include "Imgui/imgui_demo.cpp"

DIR* _mDirectory;
struct dirent* _mDirent;
std::vector<std::string> _mDirectoryList;

std::vector<std::string> Console::output = std::vector<std::string>();

Editor::Editor(Application* pApp)
	: _pApplication(pApp)
{
	//Creates the screen shader for the framebuffer
	_pScreenShader = new Shader("Resources/Shaders/fbVert.vs", "Resources/Shaders/fbFrag.fs");

	//Creates the editor framebuffer
	_pEditorFramebuffer = new Framebuffer(_pScreenShader);


	float aspectRatio = Window::GetAspectRatio();
	float zoomLevel = 1.0f;

	float left = -aspectRatio * zoomLevel;
	float right = aspectRatio * zoomLevel;
	float bottom = -zoomLevel;
	float top = zoomLevel;
}

Editor::~Editor()
{
	delete _pEditorFramebuffer;
	delete _pScreenShader;
}

void Editor::EditorLoop(Scene* currentScene, bool& editorMode, bool& paused)
{

	EditorUpdate(currentScene);
}

void Editor::EditorStartRender()
{
	_pEditorFramebuffer->BindFramebuffer();
	GLCall(glEnable(GL_DEPTH_TEST));
	_pEditorFramebuffer->BindShader();
}

void Editor::EditorRender()
{
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
	ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);

	ImGui::Begin("Freemove Camera", 0, ImGuiWindowFlags_NoSavedSettings);


	if (ImGui::IsWindowFocused())
	{
		CameraManager::GetCamera("Editor")->OnUpdate();
	}


	ImVec2 wp = ImGui::GetCursorScreenPos();
	_windowPos = { wp.x,wp.y };
	ImGui::GetWindowDrawList()->AddImage(
		(void*)_pEditorFramebuffer->GetTexture(),
		wp,
		ImVec2(Window::GetWidth(),Window::GetHeight()),
		ImVec2(0, 1.0), ImVec2(1.0, 0));

	ImVec2 ws = ImGui::GetWindowSize();
	_windowSize = { ws.x, ws.y };
	//if (_windowSize.y > Window::GetHeight() / 2.0f) _windowSize.y = Window::GetHeight() / 2.0f;

	ImGui::End();

	ConvertGameToEditorSpace();
}

void Editor::EditorEndRender()
{
	Window::SwapBuffers();
}

void Editor::ConvertGameToEditorSpace()
{
	glm::vec2 mousePos = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
	glm::vec2 editorPos = glm::vec2(0.0f);
	editorPos = { _windowPos.x, _windowPos.y };

	ImVec2 edMousePos = ImGui::GetMousePos();

	glm::vec2 cPos = { edMousePos.x - editorPos.x, edMousePos.y - editorPos.y };


	cPos /= _windowSize;
	glm::vec2 clampExtents = CameraManager::GetCamera("Editor")->Size();

	cPos *= clampExtents * 2.0f;
	cPos -= clampExtents;

	//Invert Y axis
	cPos.y *= -1.0f;


	if (cPos.x < -clampExtents.x) cPos.x = -clampExtents.x;
	else if (cPos.x > clampExtents.x) cPos.x = clampExtents.x;

	if (cPos.y < -clampExtents.y) cPos.y = -clampExtents.y;
	else if (cPos.y > clampExtents.y) cPos.y = clampExtents.y;

	_mousePosInEditorSpace = cPos;
	Input::SetEditorMousePos(cPos.x, cPos.y);
}


void Editor::EditorUpdate(Scene* currentScene)
{
	currentScene->EditorUpdate();
}
