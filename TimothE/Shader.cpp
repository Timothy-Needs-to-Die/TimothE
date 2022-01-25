#include <assert.h>

#include "Shader.h"

Shader::Shader(const std::string& vsPath, const std::string& fsPath) : _vertexShaderPath(vsPath), _fragmentShaderPath(fsPath)
{
	_shaderSourceCode = GetShadersFromFile();
	_shaderProgramID = CreateShader();
}

Shader::~Shader()
{
    UnbindShader();
    glDeleteProgram(_shaderProgramID);
}

void Shader::BindShader()
{
    glUseProgram(_shaderProgramID);
}

void Shader::UnbindShader()
{
    glUseProgram(0);
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

    glAttachShader(programID, vs);
    glAttachShader(programID, fs);
    glLinkProgram(programID);

	glLinkProgram(programID);

	GLint isLinked;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, infoLog.data());
        std::cout << "Shader linking failed (" << _shaderSourceCode.vertexShaderSource << "):\n" << infoLog.data() << std::endl;

		glDeleteProgram(programID);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

    // Shaders are now linked to a program, so we no longer need them
    glDeleteShader(vs);
    glDeleteShader(fs);

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
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus != GL_TRUE) {
        GLchar log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
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
void Shader::SetBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(GetProgramID(), name.c_str()), (int)value); }
void Shader::SetInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(GetProgramID(), name.c_str()), value); }
void Shader::SetFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(GetProgramID(), name.c_str()), value); }

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(GetProgramID(), name.c_str()), 1, &value[0]); }
void Shader::SetVec2(const std::string& name, float x, float y) const { glUniform2f(glGetUniformLocation(GetProgramID(), name.c_str()), x, y); }
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(GetProgramID(), name.c_str()), 1, &value[0]); }
void Shader::SetVec3(const std::string& name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(GetProgramID(), name.c_str()), x, y, z); }
void Shader::SetVec4(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(GetProgramID(), name.c_str()), 1, &value[0]); }
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) { glUniform4f(glGetUniformLocation(GetProgramID(), name.c_str()), x, y, z, w); }

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(GetProgramID(), name.c_str()), 1, GL_FALSE, &mat[0][0]); }
void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(GetProgramID(), name.c_str()), 1, GL_FALSE, &mat[0][0]); }
void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(GetProgramID(), name.c_str()), 1, GL_FALSE, &mat[0][0]); }
