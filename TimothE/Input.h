#pragma once

#include "TimothEInputCodes.h"

class Input
{
public:
	static void Init();

	static void SetKey(TimothEKeyCode keycode, TimothEInputState state);
	static void SetMouseButton(TimothEMouseCode button, TimothEInputState state);

	static bool IsKeyDown(TimothEKeyCode keycode);
	static bool IsKeyHeld(TimothEKeyCode keycode);
	static bool IsKeyUp(TimothEKeyCode keycode);

	static bool IsMouseButtonDown(TimothEMouseCode button);
	static bool IsMouseButtonUp(TimothEMouseCode button);

private:
	static int* _pKeyArr;
	static int* _pMouseArr;
};

