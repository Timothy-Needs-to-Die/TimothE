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

	COMPONENT_CLASS_CATEGORY(Transform_Category);
	COMPONENT_CLASS_TYPE(Transform_Type);

	Vector2D GetPosition() { return Vector2D(_xPos, _yPos); };
	float GetX() { return _xPos; }
	float GetY() { return _yPos; }
	void SetPosition(float x, float y);
	float GetXrotation() { return _xRot; };
	void SetXrotation(float xRot);

private:
	float _xPos;
	float _yPos;
	float _xRot;
	float _yRot;
	float _scaleX;
	float _scaleY;
};