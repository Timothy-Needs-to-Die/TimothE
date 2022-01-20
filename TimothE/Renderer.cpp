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
	gameObject->GetShader()->BindShader();
	
	glBindVertexArray(gameObject->GetVAO());

	glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	gameObject->GetShader()->SetMat4("projection", projection);

	glm::mat4 transform = gameObject->GetTransform()->_transformationMatrix;
	gameObject->GetShader()->SetMat4("transform", transform);

	glBindTexture(GL_TEXTURE_2D, gameObject->GetTextureID());

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
