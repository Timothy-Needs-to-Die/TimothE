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

	//glm::mat4 GetTransformationMatrix() { return _transformationMatrix; };

	int GetCategory() const override { return 0; };
	int GetType() const override { return 0; };

	glm::mat4 _transformationMatrix;
private:

	glm::vec2 _position;
	glm::vec2 _size;
	float _rotation;
};