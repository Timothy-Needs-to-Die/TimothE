#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"

class Editor
{
public:
	Editor(Window* pWindow);
	~Editor();

	//Runs through the editor loop
	void EditorLoop(Scene* currentScene, float dt, bool& editorMode);

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
	void ImGUISwitchRender(bool& editorMode);

	//Editor update loop
	void EditorUpdate(Scene* currentScene, float dt);

	Window* _pWindow;

	Framebuffer* _pEditorFramebuffer;
	Shader* _pScreenShader;
	char* _pNotesBuffer;

	GameObject* _pSelectedGameObject = nullptr;
};

