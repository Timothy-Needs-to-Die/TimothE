#pragma once

#include "Window.h"
#include "ApplicationEvent.h"

class Application
{
public:
	//Initialize the application. If true is passed in then a editor window will also be created.
	void Init(bool createEditorWindow = true);

	//Starts the game loop and the editor window loop
	void RunLoop();

	void OnEditorEvent(Event& e);
	void OnGameEvent(Event& e);

private:
	bool OnEditorWindowClose(WindowCloseEvent& e);
	bool OnGameWindowClose(WindowCloseEvent& e);

	bool OnGameWindowKeyPressedEvent(KeyPressedEvent& e);
	bool OnGameWindowKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnGameWindowMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnGameWindowMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

	//TODO: These functions may be not needed, but it could be good to capture different input depending on the window open?
	bool OnEditorWindowKeyPressedEvent(KeyPressedEvent& e);
	bool OnEditorWindowKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnEditorWindowMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnEditorWindowMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

	Window* _pGameWindow;
	Window* _pEditorWindow;

	bool _inEditorMode;
	bool _running;
};

