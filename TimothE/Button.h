#pragma once

#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Core/Events/MouseEvent.h"
#include "Texture2D.h"
#include "Input.h"
#include "Console.h"
#include "TextComponent.h"

using std::string;
using std::vector;

class Button : public Component
{
public:
	Button(GameObject* parent);
	~Button();

	COMPONENT_STATIC_TYPE(Button_Type);

	// Component Methods
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	void DrawEditorUI() override;

	// OnClick management
	void AddClickEvent(void (*function)());
	void RemoveClickEvent(void (*function)());

	// Getter & Setter
	bool IsHovering() { return _isHovering; }
	bool IsClicked() { return _isClicked; }

private:
	bool _isHovering;
	bool _isClicked;

	// OnClick Calls
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