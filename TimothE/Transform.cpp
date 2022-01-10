#include "Transform.h"

Transform::Transform()
{
	_mScaleX = 1;
	_mScaleY = 1;
	_mXpos = 0;
	_mYpos = 0;
	_mXrot = 0;
	_mYrot = 0;
}

Transform::Transform(float x, float y, float rotx, float roty, float scalex, float scaley)
{
	_mScaleX = scalex;
	_mScaleY = scaley;
	_mXpos = x;
	_mYpos = y;
	_mXrot = rotx;
	_mYrot = roty;
}

void Transform::SetPosition(float x, float y)
{
	_mXpos = x;
	_mYpos = y;
}

void Transform::SetXrotation(float xRot)
{
	_mXrot = xRot;
}

Transform::~Transform()
{

}
