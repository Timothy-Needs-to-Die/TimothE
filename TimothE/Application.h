#pragma once
#include "Window.h"


class Application
{
public:
	void Init(bool createEditorWindow = true);

	void RunLoop();

private:
	Window* _pGameWindow;
	Window* _pEditorWindow;

	bool _inEditorMode;
};

