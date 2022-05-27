#pragma once
#include "pch.h"
#include "UID.h"
#include "Component.h"
#include "ColliderBase.h"

struct Rect
{
	float xPos;
	float yPos;
	float width;
	float height;

	Rect(float x, float y, float w, float h)
	{
		xPos = x;
		yPos = y;
		width = w;
		height = h;
	}
}; 

class BoxColliderComponent : public ColliderBase		
{
public:

	COMPONENT_STATIC_TYPE(Collider)
		
	// Constructor & Deconstructor
	BoxColliderComponent(GameObject* parent);
	~BoxColliderComponent();

	// Component Methods
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	virtual void DrawEditorUI() override;

	// Getters & Setters
	bool IsEnabled() { return _isEnabled; }
	void SetEnabled(bool state) { _isEnabled = state; }

	Rect* GetCollisionRect() { return _boxCollider; }

private:
	bool _isEnabled;

	Rect* _boxCollider;

	// Editor UI
	bool* _editorIsEnabled;
};