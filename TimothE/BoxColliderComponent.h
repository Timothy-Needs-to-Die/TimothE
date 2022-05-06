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

	COMPONENT_STATIC_TYPE(Boxcollision_Type)
		
	// Constructor & Deconstructor
	BoxColliderComponent(GameObject* parent);
	~BoxColliderComponent();

	// Component Methods
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	virtual void DrawEditorUI() override;
	//virtual void GetComponent() = 0;

	// Collision Methods
	bool Intersects(Rect* box);
	bool IsPointInside(glm::vec2 point);
	
	// Getters & Setters
	bool IsEnabled() { return _isEnabled; }
	void SetEnabled(bool state) { _isEnabled = state; }

	Rect* GetCollisionRect() { return _boxCollider; }

	virtual bool SaveState(IStream& stream) const override {
		Component::SaveState(stream);

		WriteFloat(stream, _boxCollider->xPos);
		WriteFloat(stream, _boxCollider->yPos);
		WriteFloat(stream, _boxCollider->width);
		WriteFloat(stream, _boxCollider->height);
		WriteInt(stream, (int)_isEnabled);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		Component::LoadState(stream);

		_boxCollider = new Rect(
			ReadFloat(stream),
			ReadFloat(stream),
			ReadFloat(stream),
			ReadFloat(stream));

		_isEnabled = (bool)ReadInt(stream);

		return true;
	}
private:
	bool _isEnabled;

	Rect* _boxCollider;

	// Editor UI
	bool* _editorIsEnabled;
};