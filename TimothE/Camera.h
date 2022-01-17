

#pragma once

#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(GLFWwindow* window, int width, int height, float fov);


	void Update(float dt);

	float* Proj() {
		return glm::value_ptr(proj);
	}

	float* View() {
		return glm::value_ptr(view);
	}

	float* Position() {
		return glm::value_ptr(cameraPos);
	}

	glm::mat4 ProjMat() {
		return proj;
	}

	glm::mat4 ViewMat() {
		return view;
	}

	glm::vec3 GPosition() {
		return cameraPos;
	}

	float* Front() {
		return glm::value_ptr(cameraFront);
	}

	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void ProcessScrollMovement(float yOffset);

	float pitch = 0.0f;
	float yaw = -90.0f;

	float fov = 45.0f;

private:
	void PollInput(float dt);

private:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;


	glm::vec3 cameraRight;

	glm::mat4 proj;
	glm::mat4 view;



	int width;
	int height;



	GLFWwindow* _pWindow;
};

