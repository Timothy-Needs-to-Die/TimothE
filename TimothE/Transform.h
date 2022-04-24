#pragma once

#include "imgui.h"
#include "Component.h"
#include "MemoryManager.h"

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
	void DrawEditorUI() override;

	//Getters
	glm::vec2 GetPosition() const { return _position; };
	glm::vec2 GetScale() const { return _size; }
	float GetRotation() const { return _rotation; }
	glm::mat4 GetTransformMatrix() const { return _transformationMatrix; }
	Quad GetRenderQuad() const { return Quad{ _position, _size }; }

	//Setters
	void SetPosition(float x, float y) { _position = glm::vec2(x, y); }
	void SetPosition(glm::vec2 pos) { _position = pos; }
	void SetRotation(float xRot) { _rotation = xRot; }
	void SetXScale(float _tileScale) { _size.x = _tileScale; }
	void SetYScale(float _tileScale) { _size.y = _tileScale; }
	void SetScale(glm::vec2 _tileScale) { _size = _tileScale; }

	//Performs a translate operation
	void Translate(glm::vec2 newPos);
	//Performs a scale operation
	void Scale(glm::vec2 newSize);
	//Performs a rotate operation
	void Rotate(float rotationAmount, glm::vec2 axis);

	//Calculates the transform matrix. Needs to be called whenever position, rotation or scale are called
	void CalculateTransformMatrix();

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override;
	virtual bool LoadState(IStream& stream) override;
private:
	glm::mat4 _transformationMatrix;

	glm::vec2 _position;
	glm::vec2 _size;
	float _rotation;

	//These pointers are used for the ImGui Editor window
	float* editorPos;
	float* editorRot;
	float* editorScale;
};
