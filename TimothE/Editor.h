#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "Console.h"
#include "imgui.h"

#define CONTENT_BROWSER_DIRECTORY "./Resources" //sets file directory for the content browser

class Editor
{
public:
	Editor(Window* pWindow);
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
	string _mCurrentDir = CONTENT_BROWSER_DIRECTORY;
	Camera* _pEditorCamera;

	ImVec2 _windowPos;
	ImVec2 _windowSize;

	glm::vec2 _mousePosInEditorSpace;

	//Texture2D* pContentTextureImage = new Texture2D();
	//Texture2D* pContentTextureScene = new Texture2D();
	//Texture2D* pContentTextureConfig = new Texture2D();
	//Texture2D* pContentTextureScript = new Texture2D();
	//Texture2D* pContentTextureSound = new Texture2D();
	//Texture2D* pContentTextureFile = new Texture2D();
	//Texture2D* pContentTextureFolder = new Texture2D();
};
