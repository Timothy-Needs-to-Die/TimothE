#pragma once

#include "Component.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

struct Vector2D
{
	float _x, _y;

	Vector2D(float x, float y)
	{
		_x = x;
		_y = y;
	}
};

class Transform : public Component
{
public:
	Transform();
	Transform(glm::vec2 position, glm::vec2 size, float rotation);

	void Translate(glm::vec2 newPos);
	void Scale(glm::vec2 newSize);
	void Rotate(float rotationAmount, glm::vec3 axis);

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	COMPONENT_CLASS_CATEGORY(Transform_Category);
	COMPONENT_CLASS_TYPE(Transform_Type);

	glm::vec2 GetPosition() { return _position; };

	//glm::mat4 GetTransformationMatrix() { return _transformationMatrix; };



	glm::mat4 _transformationMatrix;
private:

	glm::vec2 _position;
	glm::vec2 _size;
	float _rotation;
};