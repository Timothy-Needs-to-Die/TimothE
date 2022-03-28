#pragma once

#include "pch.h"

#include "Window.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "Console.h"
#include "imgui.h"
#include "TileMapEditor.h"


class Application;

#define CONTENT_BROWSER_DIRECTORY "./Resources" //sets file directory for the content browser

class Editor
{
public:
	Editor(Application* pApp);
	~Editor();

	//Runs through the editor loop
	void EditorLoop(Scene* currentScene, bool& editorMode, bool& paused);


		//Starts the render
	void EditorStartRender();

	//Renders the scene
	void EditorRender();

	//Ends the render
	void EditorEndRender();

	void ConvertGameToEditorSpace();

	Framebuffer* _pEditorFramebuffer;
private:

	//Where all ImGui code will go
	void EditorImGui(Scene* currentScene);

	//ImGui
	void ImGUISwitchRender(bool& editorMode, bool& paused);

	//Editor update loop
	void EditorUpdate(Scene* currentScene);

	Shader* _pScreenShader;
	char* _pNotesBuffer;

	GameObject* _pSelectedGameObject = nullptr;

	void CreateFileInContentBrowser(std::string name, std::string type);
	void CheckFileType(std::string fileDirectory, int i);
	void SearchFileDirectory();
	std::string _mCurrentDir = CONTENT_BROWSER_DIRECTORY;

	bool tileEditorOpen;

	glm::vec2 _windowPos;
	glm::vec2 _windowSize;

	glm::vec2 _mousePosInEditorSpace;

	Texture2D* pImGuiSample;

	Application* _pApplication;

	Texture2D* pContentTextureImage = new Texture2D(NULL);
	Texture2D* pContentTextureScene = new Texture2D(NULL);
	Texture2D* pContentTextureConfig = new Texture2D(NULL);
	Texture2D* pContentTextureScript = new Texture2D(NULL);
	Texture2D* pContentTextureSound = new Texture2D(NULL);
	Texture2D* pContentTextureFile = new Texture2D(NULL);
	Texture2D* pContentTextureFolder = new Texture2D(NULL);
};
