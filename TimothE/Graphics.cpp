#include "Graphics.h"

void Graphics::Initialize()
{
	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
}

void Graphics::Render(GLFWwindow* window, GameObject* gameObject)
{
	_pShader->BindShader();
}
