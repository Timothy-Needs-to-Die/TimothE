#pragma once

#include "pch.h"

#include "Window.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "Console.h"
#include "imgui.h"

class Application;

#define CONTENT_BROWSER_DIRECTORY "./Resources" //sets file directory for the content browser

class Editor
{
public:
	Editor(Application* pApp, Window* pWindow);
	~Editor();

	//Runs through the editor loop
	void EditorLoop(Scene* currentScene, float dt, bool& editorMode, bool& paused);


		//Starts the render
	void EditorStartRender();

	//Renders the scene
	void EditorRender();

	//Ends the render
	void EditorEndRender();

	void ConvertGameToEditorSpace();

	Framebuffer* _pEditorFramebuffer;

	Camera* GetCamera() const { return _pEditorCamera; }

private:

	//Where all ImGui code will go
	void EditorImGui(Scene* currentScene);

	//ImGui
	void ImGUISwitchRender(bool& editorMode, bool& paused);

	//Editor update loop
	void EditorUpdate(Scene* currentScene, float dt);

	Window* _pWindow;

	Shader* _pScreenShader;
	char* _pNotesBuffer;

	GameObject* _pSelectedGameObject = nullptr;

	void CreateFileInContentBrowser();
	void SearchFileDirectory();
	std::string _mCurrentDir = CONTENT_BROWSER_DIRECTORY;
	Camera* _pEditorCamera;

	bool tileEditorOpen;

	ImVec2 _windowPos;
	ImVec2 _windowSize;

	glm::vec2 _mousePosInEditorSpace;

	Texture2D* pImGuiSample;

	Application* _pApplication;

	//Texture2D* pContentTextureImage = new Texture2D();
	//Texture2D* pContentTextureScene = new Texture2D();
	//Texture2D* pContentTextureConfig = new Texture2D();
	//Texture2D* pContentTextureScript = new Texture2D();
	//Texture2D* pContentTextureSound = new Texture2D();
	//Texture2D* pContentTextureFile = new Texture2D();
	//Texture2D* pContentTextureFolder = new Texture2D();
};
