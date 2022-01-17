#include "Camera.h"

void Camera::Onstart()
{
}

void Camera::OnUpdate()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glTranslatef(5, 100, 0);
	
	glm::mat4 projection;
	glm::mat4 view = glm::lookAt(glm::vec3{ 0,100,3 }, glm::vec3{ 0,99,2 }, glm::vec3{ 0,1,0 });;
	projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
	//glUniformMatrix4fv(glGetUniformLocation());
}

void Camera::OnEnd()
{
}
