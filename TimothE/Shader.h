#pragma once

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

struct ShaderSourceCode {
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

class Shader
{
public:
	Shader(const std::string& vsPath, const std::string& fsPath);
	~Shader();

	unsigned int GetProgramID() const { return (unsigned int)_shaderProgramID; }

	void BindShader();
	void UnbindShader();

	//UNIFORMS
	bool setUniformfv(GLint location, GLsizei count, const GLfloat* v, int numElements);

	bool setUniform1fv(GLint location, GLsizei count, const GLfloat* v) { return setUniformfv(location, count, v, 1); };
	bool setUniform2fv(GLint location, GLsizei count, const GLfloat* v) { return setUniformfv(location, count, v, 2); };
	bool setUniform3fv(GLint location, GLsizei count, const GLfloat* v) { return setUniformfv(location, count, v, 3); };
	bool setUniform4fv(GLint location, GLsizei count, const GLfloat* v) { return setUniformfv(location, count, v, 4); };
private:
	GLuint CreateShader();
	GLuint CompileShader(GLenum sType, const std::string& source);
	ShaderSourceCode GetShadersFromFile();
private:
	GLuint _shaderProgramID;
	ShaderSourceCode _shaderSourceCode;

	std::string _vertexShaderPath;
	std::string _fragmentShaderPath;
};
