#pragma once

#include "Window.h"
#include "ApplicationEvent.h"
#include "Renderer.h"
#include "Scene.h"
#include "Framebuffer.h"

class Application
{
public:
	//Initialize the application. If true is passed in then a editor window will also be created.
	void Init(bool devMode = true);

	//Starts the game loop and the editor window loop
	void GameLoop();

	void OnGameEvent(Event& e);

protected:
	void PollInput();

	void EditorUpdate(float dt);
	
	void EditorStartRender();
	void EditorRender();
	void EditorEndRender();

	void EditorImGUIRender();

	void GameBeginRender();
	void GameRender();
	void GameEndRender();
	void GameUpdate(float dt);

	void ImGUISwitchRender();

private:
	bool OnGameWindowClose(WindowCloseEvent& e);
	bool OnGameWindowKeyPressedEvent(KeyPressedEvent& e);
	bool OnGameWindowKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnGameWindowMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnGameWindowMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

	Renderer _renderer;

	Window* _pGameWindow;

	bool _inEditorMode;
	bool _devMode;

	bool _running;

	char* _pNotesBuffer;

	Scene* _pCurrentScene;

	Shader* _pScreenShader;

	Framebuffer* _pEditorFramebuffer;
};

