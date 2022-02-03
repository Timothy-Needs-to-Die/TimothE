#pragma once

#include "pch.h"

#include "Window.h"
#include "ApplicationEvent.h"
#include "Scene.h"
#include "MemoryManager.h"

#include "AudioEngine.h"
#include "TileMap.h"
#include "OpenGLError.h"

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
	void GameUpdate(float dt);

	void ImGUISwitchRender();

private:
	//Event Handlers
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnWindowKeyPressedEvent(KeyPressedEvent& e);
	bool OnWindowKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnWindowMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnWindowMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnWindowMouseMovedEvent(MouseMovedEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);

private:
	AudioEngine* _pAudio;

	bool _mInEditorMode = true;
	bool _mDevMode;

	bool _mRunning;

	Scene* _pCurrentScene;

	class Editor* _pEditor;

	bool _mPaused = false;
	bool _mGameRunning = false;

	Camera* _pGameCamera;

	TileMap* _pTilemap;
};
