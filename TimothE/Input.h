#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:
	static void Init();

	static void SetKey(int keycode, int state);
	static void SetMouseButton(int button, int state);

	static bool IsKeyDown(int keycode);
	static bool IsKeyHeld(int keycode);
	static bool IsKeyUp(int keycode);

	static bool IsMouseButtonDown(int button);
	static bool IsMouseButtonUp(int button);

private:
	static int* _pKeyArr;
	static int* _pMouseArr;
};

