#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"

class Console
{
public:
	static void Print(string message);
	static vector<string> GetConsoleOutput() { return output; }

private:
	static vector<string> output;
};

class Editor
{
public:
	Editor(Window* pWindow);
	~Editor();

	//Runs through the editor loop
	void EditorLoop(Scene* currentScene, float dt, bool& editorMode, bool& paused);

private:
	//Starts the render 
	void EditorStartRender();

	//Renders the scene
	void EditorRender();

	//Ends the render
	void EditorEndRender();
	
	//Where all ImGui code will go
	void EditorImGui(Scene* currentScene);
	
	//ImGui
	void ImGUISwitchRender(bool& editorMode, bool& paused);

	//Editor update loop
	void EditorUpdate(Scene* currentScene, float dt);

	Window* _pWindow;

	Framebuffer* _pEditorFramebuffer;
	Shader* _pScreenShader;

	GameObject* _pSelectedGameObject = nullptr;

	void SearchFileDirectory();
	string _mCurrentDir = ".";
};

