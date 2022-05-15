#include "../../pch.h"
#include <assert.h>
#include "Shader.h"
#include "OpenGLError.h"

Shader::Shader(const std::string& vsPath, const std::string& fsPath) : _vertexShaderPath(vsPath), _fragmentShaderPath(fsPath)
{
	_shaderSourceCode = GetShadersFromFile();
	_shaderProgramID = CreateShader();
}

Shader::~Shader()
{
	UnbindShader();
	GLCall(glDeleteProgram(_shaderProgramID));
}

void Shader::BindShader()
{
	GLCall(glUseProgram(_shaderProgramID));
}

void Shader::UnbindShader()
{
	GLCall(glUseProgram(0));
}

GLuint Shader::CreateShader()
{
	GLuint programID = glCreateProgram();

	if (programID == 0)
	{
		std::cout << "[ERROR]: Program ID is invalid! Program ID is equal to " << programID << "." << std::endl;
	}

	GLuint vs = CompileShader(GL_VERTEX_SHADER, _shaderSourceCode.vertexShaderSource);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, _shaderSourceCode.fragmentShaderSource);

	GLCall(glAttachShader(programID, vs));
	GLCall(glAttachShader(programID, fs));
	GLCall(glLinkProgram(programID));

	GLCall(glLinkProgram(programID));

	GLint isLinked;
	GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &isLinked));
	if (isLinked == GL_FALSE)
	{
		GLint maxLength;
		GLCall(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength));

		std::vector<GLchar> infoLog(maxLength);
		GLCall(glGetProgramInfoLog(programID, maxLength, &maxLength, infoLog.data()));
		std::cout << "Shader linking failed (" << _shaderSourceCode.vertexShaderSource << "):\n" << infoLog.data() << std::endl;

		GLCall(glDeleteProgram(programID));

		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));
	}

	// Shaders are now linked to a program, so we no longer need them
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return programID;
}

GLuint Shader::CompileShader(GLenum sType, const std::string& source)
{
	GLuint shader = glCreateShader(sType);

	if (shader == 0)
	{
		std::cout << "[ERROR]: Shader cant be compiled! Shader ID is equal to " << shader << "." << std::endl;
	}

	const char* src = source.c_str();
	GLCall(glShaderSource(shader, 1, &src, NULL));
	GLCall(glCompileShader(shader));

	GLint compileStatus;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus));

	if (compileStatus != GL_TRUE) {
		GLchar log[512];
		GLCall(glGetShaderInfoLog(shader, 512, NULL, log));
		//ADD LOGGER CODE
	}

	return shader;
}

ShaderSourceCode Shader::GetShadersFromFile()
{
	std::ifstream vsFile(_vertexShaderPath.c_str());
	std::ifstream fsFile(_fragmentShaderPath.c_str());

	std::stringstream vsSource;
	std::stringstream fsSource;

	std::string line;

	//Unsuccessful
	if (vsFile.fail())
		std::cout << "[ERROR]: Vertex Shader Error! Failed to open shader file: " << _vertexShaderPath << "." << std::endl;

	//Unsuccessful
	if (fsFile.fail())
		std::cout << "[ERROR]: Fragment Shader Error! Failed to open shader file: " << _vertexShaderPath << "." << std::endl;

	//READ EACH LINE OF FILE INTO STRING STREAM
	while (getline(vsFile, line))
		vsSource << line << '\n';

	while (getline(fsFile, line))
		fsSource << line << '\n';

	ShaderSourceCode shaderSourceCode;
	shaderSourceCode.vertexShaderSource = vsSource.str();
	shaderSourceCode.fragmentShaderSource = fsSource.str();

	return shaderSourceCode;
}

/////////////////////////////
//UNIFORM UTILITY FUNCTIONS//
/////////////////////////////
void Shader::SetBool(const std::string& name, bool value) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniform1i(GetLocation(name), (int)value)); }
void Shader::SetInt(const std::string& name, int value) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniform1i(GetLocation(name), value)); }
void Shader::SetFloat(const std::string& name, float value) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniform1f(GetLocation(name), value)); }

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniform2fv(GetLocation(name), 1, &value[0])); }
void Shader::SetVec2(const std::string& name, float x, float y) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniform2f(GetLocation(name), x, y)); }
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniform3fv(GetLocation(name), 1, &value[0])); }
void Shader::SetVec3(const std::string& name, float x, float y, float z) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniform3f(GetLocation(name), x, y, z)); }
void Shader::SetVec4(const std::string& name, const glm::vec4& value) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniform4fv(GetLocation(name), 1, &value[0])); }
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) { GLCall(glUniform4f(GetLocation(name), x, y, z, w)); }

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniformMatrix2fv(GetLocation(name), 1, GL_FALSE, &mat[0][0])); }
void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniformMatrix3fv(GetLocation(name), 1, GL_FALSE, &mat[0][0])); }
void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const { GLCall(glUseProgram(_shaderProgramID)); GLCall(glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, &mat[0][0])); }

int Shader::GetLocation(const std::string& name) const
{
	GLCall(int location = glGetUniformLocation(_shaderProgramID, name.c_str()));

	ASSERT(location != -1);

	return location;
}
