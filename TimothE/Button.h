#pragma once

#include <vector>

#include "GameObject.h"
#include "MouseEvent.h"
#include "Texture2D.h"
#include "Input.h"

using std::string;
using std::vector;

class Button : public GameObject
{
public:
	Button(string name, int width, int height);
	~Button();

	void Update(float deltaTime) override;
	void Render();

	void AddOnClickCall(void (*function)());
	void RemoveOnClickCall(void (*function)());

	// Getter & Setter
	int GetWidth() { return _width; }
	void SetWidth(int width) { _width = width; }

	int GetHeight() { return _height; }
	void SetHeight(int height) { _width = height; }

	bool IsHovering() { return _isHovering; }
	bool IsClicked() { return _isClicked; }

private:	
	int _width;
	int _height;

	bool _isHovering;
	bool _isClicked;

	vector<void(*)()> _onClickCalls;
};


/*
	Button:
		OnHoverering
		Functions for adding and removing onClickCalls
		EditorUI function

	Different textures for clicked, idle, hovered?
	Text, text colors, icons

	Enable Disable buttons. Toggle Buttons?
*/
