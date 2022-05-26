#pragma once

#include "TimothEInputCodes.h"

#include <cassert>
#include "Core.h"

class Input
{
public:
	static void Init();

	static void SetKey(TimothEKeyCode keycode, TimothEInputState state);
	static void SetMouseButton(TimothEMouseCode button, TimothEInputState state);

	static void SetMousePosition(float x, float y);
	static float GetMouseX() { return _mouseXPos; }
	static float GetMouseY() { return _mouseYPos; }
	static glm::vec2 GetMousePos() { return glm::vec2(_mouseXPos, _mouseYPos); }

	
	static glm::vec2 GetMouseScreenCoords() {
		float absX = (_mouseXPos + 1.0f) * 0.5f * 1920;
		float absY = (_mouseYPos + 1.0f) * 0.5f * 1080;
		glm::vec2 result = { absX, absY };

		//TIM_LOG_LOG("X: " << absX << ", Y: " << absY);

		return result;
	}


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

	static void SetEditorMousePos(float x, float y);
	static glm::vec2 GetEditorMousePos() { return { _mousePosXRelativetoEditor, _mousePosYRelativetoEditor }; }

private:
	//Holds each of the keys that can be queried
	static int* _pKeyArr;

	//Holds each of the mouse buttons that can be queried
	static int* _pMouseArr;

	static float _mouseXPos;
	static float _mouseYPos;

	static float _mousePosXRelativetoEditor;
	static float _mousePosYRelativetoEditor;

};

