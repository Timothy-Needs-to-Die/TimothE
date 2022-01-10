#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>

void main() {
	if (!glfwInit()) {
		std::cout << "Error Initializing GLFW" << std::endl;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test",nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		std::cout << "Error creating window" << std::endl;
		glfwTerminate();
	}

	//Syncs to monitor refresh rate
	glfwSwapInterval(1);



	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.3f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}