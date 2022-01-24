#pragma once

#include "glm.hpp"
#include <vector>
#include "Shader.h"
#include "Component.h"
#include "imgui.h"
#include "ResourceManager.h"
using std::vector;
using std::string;

class Particle
{
public:
	Particle(float life, glm::vec4 colour) : _position(0.0f), _velocity(0.0f), _colour(colour), _life(life), _maxLife(life) {}
	~Particle() {}

	float GetLife() { return _life; }
	void SetLife(float newLife) { _life = newLife; }
	void InitVertexData();
	unsigned int GetVAO() const { return _vao; }

	float GetMaxLife() { return _maxLife; }
	void SetMaxLife(float life) { _maxLife = life; }

	glm::vec2 GetPosition() { return _position; }
	void SetPosition(glm::vec2 newPos) { _position = newPos; }

	glm::vec2 GetVelocity() { return _velocity; }
	void SetVelocity(glm::vec2 newVelocity) { _velocity = newVelocity; }

	glm::vec4 GetColour() { return _colour; }
	void SetColour(glm::vec4 newColour) { _colour = newColour; }
private:
	glm::vec2 _position;
	glm::vec2 _velocity;
	glm::vec4 _colour;
	float _life;
	float _maxLife;

	unsigned int _vao;
	unsigned int _vbo;
};

class ParticleSystem : public Component
{
public:
	ParticleSystem(int count, glm::vec4 colour);
	~ParticleSystem();

	//Components Overrides
	void OnStart() override;
	void OnUpdate(float deltaTime) override;
	void OnEnd() override;
	void DrawEditorUI() override;

	void CanRespawnParticles(bool toggle);

	glm::vec2 GetParentPos() { return _parentPos; }
	void SetParentPos(glm::vec2 newParent);

	vector<Particle*> GetParticles() { return _particles; }

	Shader* GetShader() const { return _pShader; }
	void SetShader(string name);
private:
	void RespawnParticle(Particle* p);

	vector<Particle*> _particles;
	const int _maxParticles;

	glm::vec2 _parentPos;

	bool _canRespawn;

	string _shaderName;
	Shader* _pShader;
	int _shaderID;
};

