#pragma once

#include "pch.h"

#include "Window.h"
#include "ApplicationEvent.h"
#include "Scene.h"
#include "MemoryManager.h"
#include "CameraManager.h"

#include "AudioEngine.h"
#include "TileMap.h"
#include "OpenGLError.h"
#include "SpriteSheet.h"
#include "SceneManager.h"

#include "FarmScene.h"

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
	void GameUpdate();

	void ImGUISwitchRender();

private:
	//Event Handlers
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnMouseMovedEvent(MouseMovedEvent& e);
	bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);

private:
	AudioEngine* _pAudio;

	bool _mInEditorMode = true;
	bool _mDevMode;

	bool _mRunning;

	class Editor* _pEditor;

	bool _mPaused = false;
	bool _mGameRunning = false;

	Scene* _pCurrentScene;
	FarmScene* _pFarmScene;

	//TileMap* _pTilemap;
	//SpriteSheet* _pSpritesheet;
};
