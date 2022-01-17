#include "Renderer.h"

void Renderer::Initialize()
{
	
}

void Renderer::RenderDrawables(vector<GameObject*> gameObjects)
{
	for (auto& obj : gameObjects)
	{
		Render(obj);
	}
}

void Renderer::Render(GameObject* gameObject)
{
	glUseProgram(gameObject->GetShaderID());
	
	gameObject->InitVertexData();
	
	unsigned int transformLoc = glGetUniformLocation(gameObject->GetShaderID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(gameObject->GetTransform()->_transformationMatrix));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
}
