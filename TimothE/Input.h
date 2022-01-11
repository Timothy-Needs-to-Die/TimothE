#pragma once

#include "TimothEInputCodes.h"

#include <cassert>

class Input
{
public:
	static void Init();

	static void SetKey(TimothEKeyCode keycode, TimothEInputState state);
	static void SetMouseButton(TimothEMouseCode button, TimothEInputState state);

	//Is the key pressed?
	static bool IsKeyDown(TimothEKeyCode keycode);

	//Is the key held down?
	static bool IsKeyHeld(TimothEKeyCode keycode);

	//Is the key currently up?
	static bool IsKeyUp(TimothEKeyCode keycode);

	//Is the mouse button down?
	static bool IsMouseButtonDown(TimothEMouseCode button);

	//Is the mouse button currently up?
	static bool IsMouseButtonUp(TimothEMouseCode button);

private:
	//Holds each of the keys that can be queried
	static int* _pKeyArr;

	//Holds each of the mouse buttons that can be queried
	static int* _pMouseArr;
};

