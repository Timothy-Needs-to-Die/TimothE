#pragma once

#include "pch.h"

#include "Core/Graphics/Window.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Graphics/OpenGLError.h"

//For some reason forward deaclaring CameraManager causes errors
#include "CameraManager.h" 
class Scene;
class MemoryManager;
class CameraManager;
class AudioEngine;
class TileMap;
class SpriteSheet;
class SceneManager;
class FarmScene;
class ImGuiManager;
class Texture2D;
class Button;
class ResourceManager;
class Time;
class CSVReader;
class CopsConfig;
class Input;


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

	void DisplayTileEditor();

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

	bool _tileMapEditorEnabled = false;

	Scene* _pCurrentScene;

	//TileMap* _pTilemap;
	//SpriteSheet* _pSpritesheet;
};
