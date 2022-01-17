#pragma once

#include "Component.h"

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
	Transform(float x, float y, float rotx, float roty, float scalex, float scaley);

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	//int GetCategory() const override { return 0; };
	//int GetType() const override { return 0; };
	COMPONENT_CLASS_TYPE(Transform_Type);
	COMPONENT_CLASS_CATEGORY(Categories::Transform_Category);

	Vector2D* GetPosition() { return new Vector2D(_xPos, _yPos); };
	void SetPosition(float x, float y);
	float GetXrotation() { return _xRot; };
	void SetXrotation(float xRot);
	Vector2D* GetScale() { return new Vector2D(_scaleX, _scaleY); }

	

	// Inherited via ISerializable
	virtual bool Write(IStream& stream) const override {
		Component::Write(stream);

		//Save position
		WriteFloat(stream, _xPos);
		WriteFloat(stream, _yPos);

		//Save Rotation
		WriteFloat(stream, _xRot);
		WriteFloat(stream, _yRot);

		//Save Scale
		WriteFloat(stream, _scaleX);
		WriteFloat(stream, _scaleY);

		return true;

	}
	virtual bool Read(IStream& stream) override {
		Component::Read(stream);

		//Save position
		_xPos = ReadFloat(stream);
		_yPos = ReadFloat(stream);

		//Save Rotation
		_xRot = ReadFloat(stream);
		_yRot = ReadFloat(stream);

		//Save Scale
		_scaleX = ReadFloat(stream);
		_scaleY = ReadFloat(stream);

		return true;

	}
	virtual void Fixup() override {

	}

private:
	float _xPos;
	float _yPos;
	float _xRot;
	float _yRot;
	float _scaleX;
	float _scaleY;

	// Inherited via Component
	virtual void DrawEditorUI() override;
};