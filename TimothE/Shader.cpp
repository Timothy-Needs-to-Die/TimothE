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
    glUseProgram(GetProgramID());
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
        //ADD LOGGER CODE
    }

    GLuint vs = CompileShader(GL_VERTEX_SHADER, _shaderSourceCode.vertexShaderSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, _shaderSourceCode.fragmentShaderSource);

    glAttachShader(programID, vs);
    glAttachShader(programID, fs);
    glLinkProgram(programID);

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
        //ADD LOGGER CODE
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
        //ADD LOGGER CODE

    //Unsuccessful
    if (fsFile.fail())
        //ADD LOGGER CODE

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
