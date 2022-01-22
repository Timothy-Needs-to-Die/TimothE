#pragma once
#include "GameObject.h"
#include "imgui.h"
#include "Input.h"
#include "UID.h"
#include "pch.h"
#include "Component.h"

class CircleCollider : public Component
{
public:
	COMPONENT_STATIC_TYPE(Boxcollision_Type);

	CircleCollider(GameObject* parent);
	~CircleCollider();

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	//virtual void GetComponent() = 0;

	virtual void DrawEditorUI() override;

	virtual bool SaveState(IStream& stream) const override {
		//Write type
		WriteInt(stream, _type);

		//Write category
		WriteInt(stream, _category);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		return true;
	}

	//Sets the size of the collider using a vec2
	void SetColliderRadius(float radius) { _radius = radius; };
	//Gets the size of the collider as a vec2
	float GetColliderSize() { return _radius; };

	/*
	* if the collider is a trigger, an interaction/encounter could occur
	* if not set to a trigger, then typical collisions take place
	*/

	//Sets the collider to be a trigger or not
	void SetTrigger(bool isTrigger) { _isTrigger = isTrigger; };
	//Checks to see if the collider is a trigger
	bool IsTrigger() {
		return _isTrigger;
	};
private:
	float _radius;
	glm::vec2 _centre;
	bool _isTrigger;
	Rect* bounds;
};