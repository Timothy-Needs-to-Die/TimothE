#pragma once

#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "MouseEvent.h"
#include "Texture2D.h"
#include "Input.h"

using std::string;
using std::vector;

class Button : public Component
{
public:
	Button(GameObject* parent);
	~Button();

	COMPONENT_STATIC_TYPE(Buttom_Type);

	// Component Methods
	void OnStart() override;
	void OnUpdate(float deltaTime) override;
	void OnEnd() override;
	void DrawEditorUI() override;

	// OnClick management
	void AddOnClickCall(void (*function)());
	void RemoveOnClickCall(void (*function)());

	// Getter & Setter
	bool IsHovering() { return _isHovering; }
	bool IsClicked() { return _isClicked; }

	bool IsEnabled() { return _isEnabled; }
	void SetEnabled(bool state) { _isEnabled = state; }
private:	
	bool _isHovering;
	bool _isClicked;
	bool _isEnabled;

	// OnClick Calls
	vector<void(*)()> _onClickCalls;

	// Editor UI
	bool* _editorIsEnabled;
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
