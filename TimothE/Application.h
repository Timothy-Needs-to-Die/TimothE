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

	Window* _pGameWindow;
	Window* _pEditorWindow;

	bool _inEditorMode;
	bool _running;
};

