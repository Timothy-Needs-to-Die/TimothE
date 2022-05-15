#pragma once

//OpenGL Stuff
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>

#include <string>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR) {

	}
}

static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::string errorString = "";
		switch (error) {
		case GL_INVALID_ENUM:
			errorString = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_OPERATION:
			errorString = "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_INDEX:
			errorString = "GL_INVALID_INDEX";
			break;
		case GL_INVALID_VALUE:
			errorString = "GL_INVALID_ERROR";
			break;
		}

		std::cout << "[OpenGL Error]: (" << errorString << ") " << function << " " << file <<":" << line << std::endl;
		return false;
	}
	return true;
}
