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
	void ResetParticle();
	void InitVertexData();

	float GetLife() { return _currentLife; }
	void SetLife(float newLife);
	unsigned int GetVAO() const { return _vao; }

	float GetMaxLife() { return _maxLife; }
	void SetMaxLife(float life);

	//glm::vec2 GetPosition() { return _position; }
	//void SetPosition(glm::vec2 newPos) { _position = newPos; }

	glm::vec2 GetVelocity() { return _movementVec; }
	void SetVelocity(glm::vec2 newVelocity);

	glm::vec4 GetColour() { return _colour; }
	void SetColour(glm::vec4 newColour);

	Transform* GetTransform() { return _pTransform; }
	void SetTransform(Transform* newTransform);

	Texture2D* GetTexture() { return _pTexture; }

	void SetParentTransform(Transform* parentTransform);

	/// <summary> the angle for the particles to move in </summary>
	void SetAngle(float angle);
	/// <summary> turns angle into vector </summary>
	glm::vec2 CreateVector(float angle);
	/// <summary> whether or not particles will move in a random direction in range </summary>
	void ToggleRandomDirection(bool useRand);
	/// <summary> the range that particles can be when random </summary>
	void SetAngleRange(float range);
	void SetSpeed(float speed);

	bool GetUsingTexture() { return _usingTexture; }
	void SetUsingTexture(bool useTexture);

	bool GetCanRespawn() { return _canRespawn; }
	void SetCanRespawn(bool canRespawn);
private:
	Transform* _pTransform;
	glm::vec2 _movementVec;
	glm::vec4 _colour;
	float _speed;
	float _currentLife;
	float _maxLife;
	Texture2D* _pTexture;
	unsigned int _vao;
	unsigned int _vbo;
	Transform* _pParentTransform;
	bool _useRandomDirection;
	float _angleRange;
	float _angle;
	bool _usingTexture;
	bool _canRespawn;
};