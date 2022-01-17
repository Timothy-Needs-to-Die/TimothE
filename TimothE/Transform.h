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

	void DrawEditorUI() override;

	Vector2D GetPosition() { return Vector2D(_xPos, _yPos); };
	void SetPosition(float x, float y);
	float GetXrotation() { return _xRot; };
	float GetYrotation() { return _yRot; };
	void SetXrotation(float xRot);
	Vector2D GetScale() { return Vector2D(_scaleX, _scaleY); }

	

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
	void SetYrotation(float yRot);
	float GetXScale() { return _scaleX; }
	float GetYScale() { return _scaleY; }
	void SetXScale(float scale);
	void SetYScale(float scale);

private:
	float _xPos;
	float _yPos;
	float _xRot;
	float _yRot;
	float _scaleX;
	float _scaleY;
};