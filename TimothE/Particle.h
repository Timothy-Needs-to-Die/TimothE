#pragma once

#include "glm.hpp"
#include <vector>
#include "Shader.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Transform.h"

using std::string;
using std::vector;

class Particle
{
public:
	Particle(float life, glm::vec4 colour, Texture2D* texture, Transform* parentTransform);
	~Particle() {}

	void Update(float deltaTime);

	float GetLife() { return _life; }
	void SetLife(float newLife) { _life = newLife; }
	void InitVertexData();
	unsigned int GetVAO() const { return _vao; }

	float GetMaxLife() { return _maxLife; }
	void SetMaxLife(float life) { _maxLife = life; }

	void ResetParticle();

	//glm::vec2 GetPosition() { return _position; }
	//void SetPosition(glm::vec2 newPos) { _position = newPos; }

	glm::vec2 GetVelocity() { return _velocity; }
	void SetVelocity(glm::vec2 newVelocity) { _velocity = newVelocity; }

	glm::vec4 GetColour() { return _colour; }
	void SetColour(glm::vec4 newColour) { _colour = newColour; }

	Transform* GetTransform() { return _pTransform; }
	void SetTransform(Transform* newTransform);

	int GetTextureID() { return _pTexture->GetID(); }

	void SetParentTransform(Transform* parentTransform);
private:
	Transform* _pTransform;
	//glm::vec2 _position;
	glm::vec2 _velocity;
	glm::vec4 _colour;
	float _life;
	float _maxLife;

	Texture2D* _pTexture;

	unsigned int _vao;
	unsigned int _vbo;

	Transform* _pParentTransform;
};