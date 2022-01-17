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
	
	glBindVertexArray(gameObject->GetVAO());
	
	unsigned int transformLoc = glGetUniformLocation(gameObject->GetShaderID(), "transform");
	unsigned int projectionLoc = glGetUniformLocation(gameObject->GetShaderID(), "projection");


	glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 transform = gameObject->GetTransform()->_transformationMatrix;

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE0, gameObject->GetTextureID());

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
