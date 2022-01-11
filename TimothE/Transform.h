#pragma once

struct Vector2D
{
	float _x, _y;

	Vector2D(float x, float y)
	{
		_x = x;
		_y = y;
	}
};

class Transform
{
public:
	Transform();
	Transform(float x, float y, float rotx, float roty, float scalex, float scaley);

	Vector2D* GetPosition() { return new Vector2D(_mXpos, _mYpos); };
	void SetPosition(float x, float y);
	float GetXrotation() { return _mXrot; };
	void SetXrotation(float xRot);

	~Transform();

private:
	float _mXpos;
	float _mYpos;
	float _mXrot;
	float _mYrot;
	float _mScaleX;
	float _mScaleY;
};