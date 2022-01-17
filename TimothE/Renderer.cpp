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
	
	//gameObject->GetTransform()->Translate(glm::vec2(0.0001f, 0.0f));
	//gameObject->GetTransform()->Scale(glm::vec2(1.0f, 1.0f));
	//glm::mat4 transform = gameObject->GetTransform()->_transformationMatrix;
	gameObject->GetTransform()->Translate(glm::vec2(0.01, 0.01f));
	glm::mat4 transform2 = gameObject->GetTransform()->_transformationMatrix;

	glm::mat4 transform = glm::mat4(1.0);
	transform = glm::translate(transform, glm::vec3(0.4f, 0.3f, 0.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
