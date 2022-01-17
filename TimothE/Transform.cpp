#include "Transform.h"

Transform::Transform() 
{
	_position = { 0,0 };
	_size = { 1, 1 };
	_rotation = 0;
	_transformationMatrix = glm::mat4(1.0f);
	_transformationMatrix = glm::scale(_transformationMatrix, { _size, 0 });

}

Transform::Transform(glm::vec2 position, glm::vec2 size, float rotation) : _position(position), _size(size), _rotation(rotation)
{
	_transformationMatrix = glm::mat4(1.0f);
	_transformationMatrix = glm::scale(_transformationMatrix, glm::vec3(_size, 0 ));
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(position, 0));
}

void Transform::Translate(glm::vec2 newPos)
{
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(newPos.x, newPos.y, 0));
}

void Transform::Scale(glm::vec2 newSize)
{
	_transformationMatrix = glm::scale(_transformationMatrix, { newSize, 0 });
}

void Transform::Rotate(float rotationAmount, glm::vec3 axis)
{
	_transformationMatrix = glm::rotate(_transformationMatrix, rotationAmount, axis);
}

void Transform::OnStart()
{

}

void Transform::OnUpdate()
{
}

void Transform::OnEnd()
{
}
