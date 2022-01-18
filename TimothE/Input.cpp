#include "Input.h"


void Input::Init()
{
	//Sets the default state for each key to RELEASED
	for (int i = 0; i < KEY_LAST; ++i) {
		_pKeyArr[i] = RELEASE;
	}

	//Sets the default state for each mouse button to RELEASED	
	for (int i = 0; i < BUTTON_LAST; ++i) {
		_pMouseArr[i] = RELEASE;
	}
}

void Input::SetKey(TimothEKeyCode keycode, TimothEInputState state)
{
	//Check that the desired key code is within the array
	assert(keycode <= KEY_LAST&& keycode >= KEY_FIRST);

	_pKeyArr[keycode] = state;
}

void Input::SetMouseButton(TimothEMouseCode button, TimothEInputState state)
{
	//Checks that the desired mouse button is within the array
	assert(button <= BUTTON_LAST && button >= BUTTON_FIRST);

	_pMouseArr[button] = state;
}

void Input::SetMousePosition(float x, float y)
{
	_mouseXPos = x;
	_mouseYPos = y;
}

bool Input::IsKeyDown(TimothEKeyCode keycode)
{
	return _pKeyArr[keycode] == GLFW_PRESS;
}

bool Input::IsKeyHeld(TimothEKeyCode keycode)
{
	return _pKeyArr[keycode] == GLFW_REPEAT;
}

bool Input::IsKeyUp(TimothEKeyCode keycode)
{
	return _pKeyArr[keycode] == GLFW_RELEASE;
}

bool Input::IsMouseButtonDown(TimothEMouseCode button)
{
	return _pMouseArr[button] == GLFW_PRESS;
}

bool Input::IsMouseButtonUp(TimothEMouseCode button)
{
	return _pMouseArr[button] == GLFW_RELEASE;
}

//Initialize static members
int* Input::_pKeyArr = new int[KEY_LAST];
int* Input::_pMouseArr = new int[BUTTON_LAST];
float Input::_mouseXPos = 0.0f;
float Input::_mouseYPos = 0.0f;
