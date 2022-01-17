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

	void DrawEditorUI() override;

	glm::vec2 GetPosition() { return _position; };
	void SetPosition(float x, float y) { _position = glm::vec2(x, y); }
	void SetRotation(float xRot) { _rotation = xRot; }



	// Inherited via ISerializable
	virtual bool Write(IStream& stream) const override {
		Component::Write(stream);

		//Save position
		WriteFloat(stream, _position.x);
		WriteFloat(stream, _position.y);

		//Save Rotation
		WriteFloat(stream, _rotation);

		//Save Scale
		WriteFloat(stream, _size.x);
		WriteFloat(stream, _size.y);

		return true;

	}
	virtual bool Read(IStream& stream) override {
		Component::Read(stream);

		//Save position
		_position = glm::vec2(ReadFloat(stream), ReadFloat(stream));

		//Save Rotation
		_rotation = ReadFloat(stream);

		//Save Scale
		_size = glm::vec2(ReadFloat(stream), ReadFloat(stream));

		return true;

	}
	virtual void Fixup() override {

	}

	glm::vec2 GetScale() { return _size; }
	void SetXScale(float scale) { _size.x = scale; }
	void SetYScale(float scale) { _size.y = scale; }
	void SetScale(glm::vec2 scale) { _size = scale; }


	float GetRotation() { return _rotation; }

	//glm::mat4 GetTransformationMatrix() { return _transformationMatrix; };


	glm::mat4 _transformationMatrix;
private:

	glm::vec2 _position;
	glm::vec2 _size;
	float _rotation;
};
