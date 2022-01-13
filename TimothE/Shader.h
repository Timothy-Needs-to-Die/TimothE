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

	/////////////////////////////
	//UNIFORM UTILITY FUNCTIONS//
	/////////////////////////////
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w);

	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
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
