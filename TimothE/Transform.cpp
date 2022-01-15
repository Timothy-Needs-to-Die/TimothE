#include "Transform.h"

Transform::Transform() : Component()
{
	_scaleX = 1;
	_scaleY = 1;
	_xPos = 0;
	_yPos = 0;
	_xRot = 0;
	_yRot = 0;
}

Transform::Transform(float x, float y, float rotx, float roty, float scalex, float scaley) : Component()
{
	_scaleX = scalex;
	_scaleY = scaley;
	_xPos = x;
	_yPos = y;
	_xRot = rotx;
	_yRot = roty;
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

void Transform::SetPosition(float x, float y)
{
	_xPos = x;
	_yPos = y;
}

void Transform::SetXrotation(float xRot)
{
	_xRot = xRot;
}

void Transform::SetYrotation(float yRot)
{
	_yRot = yRot;
}

void Transform::SetXScale(float scale)
{
	_scaleX = scale;
}

void Transform::SetYScale(float scale)
{
	_scaleY = scale;
}
