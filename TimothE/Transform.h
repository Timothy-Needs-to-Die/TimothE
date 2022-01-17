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

	int GetCategory() const override { return Transform_Category; };
	int GetType() const override { return Transform_Type; };

	void EditorUI() override;

	Vector2D* GetPosition() { return new Vector2D(_xPos, _yPos); };
	void SetPosition(float x, float y);
	float GetXrotation() { return _xRot; };
	float GetYrotation() { return _yRot; };
	void SetXrotation(float xRot);
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