#include "Camera.h"

void Camera::Onstart()
{
}

void Camera::OnUpdate()
{
	//updates camera position and rotation
	glLoadIdentity();
	gluLookAt(_mTransform.GetPosition()->_x, _mTransform.GetPosition()->_y,0.0f,
			  _mTransform.GetPosition()->_x , _mTransform.GetPosition()->_y + _mTransform.GetXrotation(),0,
				1.0f,0,0);
	glRotatef(_mTransform.GetXrotation(), 1, 0, 0);
	glRotatef(_mTransform.GetXrotation(), 0, 1, 0);//y
	glRotatef(_mTransform.GetXrotation(), 0, 0, 1);//z
	glTranslatef(_mTransform.GetPosition()->_x, _mTransform.GetPosition()->_y, 0);
}

void Camera::OnEnd()
{
}
