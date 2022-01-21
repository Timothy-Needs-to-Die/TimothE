#pragma once

#include "Window.h"
#include "ApplicationEvent.h"
#include "Renderer.h"
#include "Scene.h"
#include "MemoryManager.h"

#include "AudioEngine.h"

class Editor;

class Application
{
public:
	//Initialize the application. If true is passed in then a editor window will also be created.
	void Init(bool devMode = true);

	//Starts the game loop and the editor window loop
	void GameLoop();

	void OnGameEvent(Event& e);

	void GameStart();

protected:
	void PollInput();

	void GameBeginRender();
	void GameRender(Camera* cam);
	void GameEndRender();
	void GameUpdate(float dt);

	void ImGUISwitchRender();

private:
	//Event Handlers
	bool OnGameWindowClose(WindowCloseEvent& e);
	bool OnGameWindowKeyPressedEvent(KeyPressedEvent& e);
	bool OnGameWindowKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnGameWindowMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnGameWindowMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnGameWindowMouseMovedEvent(MouseMovedEvent& e);

private:
	AudioEngine* _audio;

	Renderer* _renderer;

	Window* _pWindow;

	bool _inEditorMode = true;
	bool _devMode;

	bool _running;

	Scene* _pCurrentScene;

	class Editor* _pEditor;

	bool _paused = false;
	bool _gameRunning = false;

	Camera* _pGameCamera;
};

