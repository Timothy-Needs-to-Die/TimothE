#pragma once

#include "glm.hpp"
#include <vector>
#include "Core/Graphics/Shader.h"
#include "Component.h"
#include "imgui.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Particle.h"
using std::vector;
using std::string;

class ParticleSystem : public Component
{
public:
	COMPONENT_STATIC_TYPE(ParticleSystem_Type);

	ParticleSystem(int count, glm::vec4 colour, Texture2D* texture, Transform* parentTransform);
	~ParticleSystem();

	//Components Overrides
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	void DrawEditorUI() override;

	void SetCanRespawnParticles(bool toggle);

	Transform* GetParentPos() { return _pParentTransform; }
	void SetParentTransform(Transform* parentTransform);

	vector<Particle*> GetParticles() { return _particles; }

	Shader* GetShader() const { return _pShader; }
	void SetShader(string name);

	void RespawnParticle(Particle* p, bool active);
	void StartConstant();
	void Burst();
	void Stop();

	void SetActive(bool active);

private:
	void CreateParticles();

	vector<Particle*> _particles;
	int _maxParticles;

	bool _creatingParticles;
	float _spawnDelay;

	glm::vec4 _particleColour;
	float _particleLife;

	Transform* _pParentTransform;

	string _shaderName;
	Shader* _pShader;
	int _shaderID;

	Texture2D* _pTexture;
};

