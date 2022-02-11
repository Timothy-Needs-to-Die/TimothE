#pragma once
#include "GameObject.h"
#include "imgui.h"
#include "Input.h"
#include "UID.h"
#include "pch.h"
#include "ColliderBase.h"

class CircleCollider : public ColliderBase
{
public:
	COMPONENT_STATIC_TYPE(Boxcollision_Type);

	CircleCollider(GameObject* parent);
	~CircleCollider();

	void OnStart() override;
	void OnUpdate(float deltaTime) override;
	void OnEnd() override;
	//virtual void GetComponent() = 0;

	virtual void DrawEditorUI() override;

	virtual bool SaveState(IStream& stream) const override {
		Component::SaveState(stream);

		WriteFloat(stream, _radius);
		WriteVec2(stream, _centre);
		WriteInt(stream, (int)_isTrigger);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		Component::LoadState(stream);

		_radius = ReadFloat(stream);
		_centre = ReadVec2(stream);
		_isTrigger = (bool)ReadInt(stream);

		return true;
	}

	//Sets the size of the collider using a vec2
	void SetColliderRadius(float radius) { _radius = radius; };
	//Gets the size of the collider as a vec2
	float GetColliderSize() { return _radius; };
	glm::vec2 GetPosition() { return _pParentObject->GetTransform()->GetPosition(); }


private:
	float _radius;
	glm::vec2 _centre;
};