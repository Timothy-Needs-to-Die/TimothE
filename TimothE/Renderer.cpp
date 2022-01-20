#include "Renderer.h"

void Renderer::RenderDrawables(vector<GameObject*> gameObjects, Camera* cam)
{
	for (auto& obj : gameObjects)
	{
		Render(obj, cam);
	}
}

void Renderer::Render(GameObject* gameObject, Camera* cam)
{
	gameObject->GetShader()->BindShader();
	
	glBindVertexArray(gameObject->GetVAO());

	gameObject->GetShader()->SetMat4("projection", cam->ProjMat());

	glm::mat4 transform = gameObject->GetTransform()->GetTransformMatrix();
	gameObject->GetShader()->SetMat4("model", transform);

	gameObject->GetShader()->SetMat4("view", cam->ViewMat());

	glBindTexture(GL_TEXTURE_2D, gameObject->GetTextureID());

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
