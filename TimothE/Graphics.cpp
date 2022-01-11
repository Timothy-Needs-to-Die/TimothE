#include "Graphics.h"

void Graphics::Initialize()
{

}

void Graphics::Render(GLFWwindow* window, GameObject* gameObject)
{
	
}

void Graphics::BindShader(unsigned int vertexShader)
{
	if (vertexShader < 1)
		return;

	glUseProgram(vertexShader);
}
