#pragma once

#include "glm.hpp"
#include <vector>
#include "Shader.h"
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
	void OnUpdate(float deltaTime) override;
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

	virtual bool SaveState(IStream& stream) const override {
		Component::SaveState(stream);

		WriteInt(stream, _maxParticles);
		
		WriteVec4(stream, _particleColour);

		WriteString(stream, _shaderName);

		WriteVec4(stream, _particleColour);

		WriteFloat(stream, _particleLife);

		//TODO: this depends on a texture component something needs to be done about supporting this

		return true;
	}

	virtual bool LoadState(IStream& stream) override {
		Component::LoadState(stream);

		_maxParticles = ReadInt(stream);
		_particleColour = ReadVec4(stream);
		_shaderName = ReadString(stream);
		_particleColour = ReadVec4(stream);
		_particleLife = ReadFloat(stream);

		CreateParticles();

		return true;
	}

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

