#pragma once

#include <GLFW/glfw3.h>
#include <GL/gl.h>

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
