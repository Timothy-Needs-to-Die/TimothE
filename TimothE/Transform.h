#pragma once

#include "Component.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Transform : public Component
{
public:
	Transform();

	void Translate(glm::vec2 newPos);
	void Scale(glm::vec2 newSize);
	void Rotate(float rotationAmount, glm::vec2 axis);

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	//int GetCategory() const override { return Transform_Category; };
	//int GetType() const override { return Transform_Type; };

	void EditorUI() override;

	COMPONENT_CLASS_CATEGORY(Transform_Category);
	COMPONENT_CLASS_TYPE(Transform_Type);

	glm::vec2 GetPosition() { return _position; };
	//void SetPosition(glm::vec2 position) { _position = position; };

	float GetRotation() { return _rotation; }
	//void SetRotation(float rotation) { _rotation = rotation; }

	//glm::mat4 GetTransformationMatrix() { return _transformationMatrix; };

	glm::vec2 GetScale() { return _size; }
	//void SetScale(glm::vec2 scale) { _size = scale; }

	glm::mat4 _transformationMatrix;
private:

	glm::vec2 _position;
	glm::vec2 _size;
	float _rotation;
};