#pragma once

#include "pch.h"

#include "Core/Graphics/Window.h"
#include "Core/Graphics/Framebuffer.h"
#include "Core/Graphics/Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "Console.h"
#include "imgui.h"
#include "TileMapEditor.h"


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

	//Ends the render
	void EditorEndRender();

	void ConvertGameToEditorSpace();

	Framebuffer* _pEditorFramebuffer;
private:
	//Editor update loop
	void EditorUpdate(Scene* currentScene);

	Shader* _pScreenShader;
	char* _pNotesBuffer;

	bool tileEditorOpen;

	glm::vec2 _windowPos;
	glm::vec2 _windowSize;

	glm::vec2 _mousePosInEditorSpace;

	Texture2D* pImGuiSample;

	Application* _pApplication;
};
