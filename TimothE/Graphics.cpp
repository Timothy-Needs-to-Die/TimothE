#include <GL/glew.h>
#include "Graphics.h"

void Graphics::Initialize()
{
	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
}

void Graphics::Render(vector<GameObject*> gameObjects)
{
	_pShader->BindShader();

	for (auto& object : gameObjects)
	{
		//bind relevant shader
		//Render GameObject
	}
}
