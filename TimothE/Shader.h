#pragma once

#include <gl/glew.h>

#include "pch.h"

//Structure to hold the source code for the shaders
struct ShaderSourceCode {
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

class Shader
{
public:
	//Constructor for taking in a vertex shader and a fragment shader path
	Shader(const std::string& vsPath, const std::string& fsPath);
	~Shader();

	//Getters
	unsigned int GetProgramID() const { return (unsigned int)_shaderProgramID; }
	std::string GetVsPath() const { return _vertexShaderPath; }
	std::string GetFsPath() const { return _fragmentShaderPath; }

	/////////////////////////////
	//UNIFORM UTILITY FUNCTIONS//
	/////////////////////////////
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	void SetVec2(const std::string& name, const glm::vec2& value) const;
	void SetVec2(const std::string& name, float x, float y) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w);

	void SetMat2(const std::string& name, const glm::mat2& mat) const;
	void SetMat3(const std::string& name, const glm::mat3& mat) const;
	void SetMat4(const std::string& name, const glm::mat4& mat) const;
	
	//GL Handlers
	void BindShader();
	void UnbindShader();
private:
	//Creates a shader based on the current data
	GLuint CreateShader();
	//Compiles a shader based on the type passed in and the source code
	GLuint CompileShader(GLenum sType, const std::string& source);
	ShaderSourceCode GetShadersFromFile();
private:
	//Stores the shader id
	GLuint _shaderProgramID;

	//Stores the source code for the shaders
	ShaderSourceCode _shaderSourceCode;

	//Stores the filepaths to each shader
	std::string _vertexShaderPath;
	std::string _fragmentShaderPath;
};
