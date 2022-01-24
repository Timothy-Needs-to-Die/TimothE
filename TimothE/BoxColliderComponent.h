#pragma once
#include "pch.h"
#include "UID.h"
#include "Component.h"

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

class BoxColliderComponent : public Component		
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

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override;
	virtual bool LoadState(IStream& stream) override;
private:
	bool _isEnabled;
	Rect* _boxCollider;

	// Editor UI
	bool* _editorIsEnabled;
	void Load(std::string data);
};