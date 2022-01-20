#pragma once

#include <vector>

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
	void OnUpdate() override;
	void OnEnd() override;
	void DrawEditorUI() override;

	// OnClick management
	void AddOnClickCall(void (*function)());
	void RemoveOnClickCall(void (*function)());

	// Getter & Setter
	bool IsHovering() { return _isHovering; }
	bool IsClicked() { return _isClicked; }

private:	
	bool _isHovering;
	bool _isClicked;

	// OnClick Calls
	vector<void(*)()> _onClickCalls;

	// Editor UI
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
