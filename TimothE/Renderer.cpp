#include "Renderer.h"
#include "ParticleSystem.h"

void Renderer::RenderDrawables(std::vector<GameObject*> gameObjects, Camera* cam)
{
	for (auto& obj : gameObjects)
	{
		Render(obj, cam);
		ParticleSystem* p = obj->GetComponent<ParticleSystem>();
		if(p != nullptr)
			Render(p, cam);
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

void Renderer::Render(ParticleSystem* particles, Camera* cam)
{
	Shader* particleShader = particles->GetShader();

	for (Particle* p : particles->GetParticles())
	{
		if (p->GetLife() > 0.0f)
		{
			particleShader->SetVec2("offset", p->GetPosition());
			particleShader->SetVec4("colour", p->GetColour());
			particleShader->BindShader();
			glBindVertexArray(p->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
}
