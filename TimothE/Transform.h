#pragma once

#include "imgui.h"
#include "Component.h"

#include "pch.h"
#include "Quad.h"

class Transform : public Component
{
public:
	Transform(GameObject* pParent);

	COMPONENT_STATIC_TYPE(Transform_Type)

	//Components Overrides
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	//Getters
	glm::vec2 GetPosition() const { return _localPosition; };
	glm::vec2 GetScale() const { return _size; }
	float GetRotation() const;
	Quad GetRenderQuad() const { return _renderQuad; }
	glm::vec2 GetForward() const { return _forward; }

	//Setters
	void SetPosition(float x, float y) { _localPosition = glm::vec2(x, y); }
	void SetPosition(glm::vec2 pos) { _localPosition = pos; }
	void SetRotation(float xRot) { _rotation = xRot; _renderQuad.rotation = _rotation; }
	void SetXScale(float _tileScale) { _size.x = _tileScale; _renderQuad.size.x = _tileScale; }
	void SetYScale(float _tileScale) { _size.y = _tileScale; _renderQuad.size.y = _tileScale; }
	void SetScale(glm::vec2 _tileScale) { _size = _tileScale; _renderQuad.size = _tileScale; }
	void SetForward(const glm::vec2 forward) { _forward = forward; }

private:
	glm::vec2 _globalPosition;
	glm::vec2 _localPosition;
	glm::vec2 _size;
	glm::vec2 _forward;

	Quad _renderQuad;

	float _rotation;
};
