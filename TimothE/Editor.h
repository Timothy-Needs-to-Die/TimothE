#pragma once

#include "pch.h"

#include "Core/Graphics/Window.h"
#include "Core/Graphics/Framebuffer.h"
#include "Core/Graphics/Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "Console.h"
#include "imgui.h"


class Application;

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

	Framebuffer* _pEditorFramebuffer = nullptr;
private:

	Shader* _pScreenShader = nullptr;

	Application* _pApplication = nullptr;
};
