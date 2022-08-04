#pragma once

#include "pch.h"

#include "Core/Graphics/Window.h"
#include "Core/Events/ApplicationEvent.h"
#include "Scene.h"
#include "CameraManager.h"

#include "AudioEngine.h"
#include "TileMap.h"
#include "Core/Graphics/OpenGLError.h"
#include "SpriteSheet.h"
#include "SceneManager.h"

#include "FarmScene.h"

class Application
{
public:
	//Initialize the application. If true is passed in then a editor window will also be created.
	void Init();

	//Starts the game loop and the editor window loop
	void GameLoop();

	void OnGameEvent(Event& e);

	void GameStart();

protected:
	void PollInput();

	void GameBeginRender();
	void GameRender(std::shared_ptr<Camera> cam);
	void GameUpdate();
private:
	//Event Handlers
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnMouseMovedEvent(MouseMovedEvent& e);
	bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	bool OnWindowFocusEvent(WindowFocusedEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);

private:
	std::shared_ptr<class AudioEngine> _pAudio = nullptr;

	bool _inEditorMode = false;
	bool _running;
	bool _paused = false;
	bool _gameRunning = false;

	class std::shared_ptr<class Editor> _pEditor;

};
