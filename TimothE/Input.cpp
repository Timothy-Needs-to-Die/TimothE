#include "Input.h"


void Input::Init()
{
	for (int i = 0; i < GLFW_KEY_LAST; ++i) {
		_pKeyArr[i] = GLFW_RELEASE;
	}

	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i) {
		_pMouseArr[i] = GLFW_RELEASE;
	}
}

//TODO: Range check keycode so it does not go outside array
void Input::SetKey(int keycode, int state)
{
	_pKeyArr[keycode] = state;
}

//TODO: Range check button so it does not go outside array
void Input::SetMouseButton(int button, int state)
{
	_pMouseArr[button] = state;
}

bool Input::IsKeyDown(int keycode)
{
	return _pKeyArr[keycode] == GLFW_PRESS;
}

bool Input::IsKeyHeld(int keycode)
{
	return _pKeyArr[keycode] == GLFW_REPEAT;
}

bool Input::IsKeyUp(int keycode)
{
	return _pKeyArr[keycode] == GLFW_RELEASE;
}

bool Input::IsMouseButtonDown(int button)
{
	return _pMouseArr[button] == GLFW_PRESS;
}

bool Input::IsMouseButtonUp(int button)
{
	return _pMouseArr[button] == GLFW_RELEASE;
}

int* Input::_pKeyArr = new int[GLFW_KEY_LAST];
int* Input::_pMouseArr = new int[GLFW_MOUSE_BUTTON_LAST];
