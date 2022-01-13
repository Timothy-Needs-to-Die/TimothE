#include "Camera.h"

void Camera::Onstart()
{
}

void Camera::OnUpdate()
{
	//updates camera position and rotation
	glLoadIdentity();
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	/*gluLookAt(_mTransform.GetPosition()->_x, _mTransform.GetPosition()->_y, 0.0f,
		_mTransform.GetPosition()->_x, _mTransform.GetPosition()->_y + _mTransform.GetXrotation(), 0,
		1.0f, 0, 0);*/
	//glRotatef(_mTransform.GetXrotation(), 1, 0, 0);
	//glRotatef(_mTransform.GetXrotation(), 0, 1, 0);//y
	//glRotatef(_mTransform.GetXrotation(), 0, 0, 1);//z
	//glTranslatef(_mTransform.GetPosition()->_x, _mTransform.GetPosition()->_y, 0);
	//glm::mat4 projection;
	//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::OnEnd()
{
}
