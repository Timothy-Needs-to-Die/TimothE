#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "Console.h"

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
};
