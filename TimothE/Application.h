#pragma once

#include "Window.h"

class Application
{
public:
	//Initialize the application. If true is passed in then a editor window will also be created.
	void Init(bool createEditorWindow = true);

	//Starts the game loop and the editor window loop
	void RunLoop();

private:
	Window* _pGameWindow;
	Window* _pEditorWindow;

	bool _inEditorMode;
};

