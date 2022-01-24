#pragma once

#include "imgui.h"
#include "Component.h"
#include "MemoryManager.h"

#include "pch.h"

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

	//Setters
	void SetPosition(float x, float y) { _position = glm::vec2(x, y); }
	void SetRotation(float xRot) { _rotation = xRot; }
	void SetXScale(float scale) { _size.x = scale; }
	void SetYScale(float scale) { _size.y = scale; }
	void SetScale(glm::vec2 scale) { _size = scale; }

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
