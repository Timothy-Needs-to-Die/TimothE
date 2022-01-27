#include "ParticleSystem.h"
#include "misc/cpp/imgui_stdlib.h"

ParticleSystem::ParticleSystem(int count, glm::vec4 colour, Texture2D* texture, Transform* parentTransform) : _maxParticles(count), _particleColour(colour), _pTexture(texture), _pParentTransform(parentTransform), _continuous(true)
{
	//Sets the type and category for the component
	SetType(Component::ParticleSystem_Type);
	SetCategory(Component::Graphics_Category);

	SetShader("default");

	_canRespawn = true;

	_particleLife = 1.0f;
	for (int i = 0; i < count; i++)
	{
		Particle* p = new Particle(_particleLife, colour, _pTexture, _pParentTransform);
		_particles.push_back(p);
		p->ResetParticle();
	}
}

ParticleSystem::~ParticleSystem()
{
	
}

void ParticleSystem::OnStart()
{
}

void ParticleSystem::OnUpdate(float deltaTime)
{
	// for each particle
	for (Particle* p : _particles)
	{
		// reduce particle life by deltatime
		p->SetLife(p->GetLife() - deltaTime);
		if (p->GetLife() > 0.0f) // if life greater than 0, still alive so update
		{
			p->SetParentTransform(_pParentTransform);
			p->Update(deltaTime);

			//p->SetPosition(p->GetPosition() + (p->GetVelocity() * deltaTime));
		}
		else // life lower than 0, particle no longer alive
		{
			if (_canRespawn)
			{
				ResetParticle(p);
			}
		}
	}
}

void ParticleSystem::OnEnd()
{
}

void ParticleSystem::DrawEditorUI()
{
	ImGui::Text("Particle System");

	if (ImGui::CollapsingHeader("Settings"))
	{
		// create input field to change max amount of particles
		static int* maxparticles = &_maxParticles;
		if (ImGui::InputInt("Max particles", maxparticles))
		{
			if (_maxParticles < 0)
				_maxParticles = 0;

			// if the value is changed, change the number of particles in vector
			int dif = _maxParticles - _particles.size();
			if (_maxParticles > _particles.size())
			{
				for (int i = 0; i < dif; i++)
				{
					// add new particles
					_particles.push_back(new Particle(_particleLife, _particleColour, _pTexture, _pParentTransform));
				}
			}
			else
			{
				for (int i = (_particles.size() - 1); i > (_maxParticles - 1); i--)
				{
					// remove and delete particles exceeding max amount
					Particle* p = _particles[i];
					_particles.erase(_particles.begin() + i);
					delete p;
				}
			}

			for (Particle* p : _particles)
			{
				ResetParticle(p);
			}
		}

		// add a radio button to choose whether particles use textures or colour
		static int texOrColour = (int)_particles[0]->GetUsingTexture();
		static float colour[4]{ 1.0f,1.0f,1.0f,1.0f };
		if (ImGui::RadioButton("Texture", &texOrColour, 1))
		{
			for (Particle* p : _particles)
			{
				p->SetUsingTexture(true);
			}
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Colour", &texOrColour, 0))
		{
			for (Particle* p : _particles)
			{
				p->SetUsingTexture(false);
			}
		}
		if (texOrColour == 1) // put this after to have these under the radio buttons, not between
		{
			if (ImGui::CollapsingHeader("Particle texture"))
			{
				ImTextureID texID = (void*)_particles[0]->GetTexture()->GetID();
				ImGui::Image(texID, ImVec2(50.0f, 50.0f));

				static std::string texPath = "lenna3.jpg";
				ImGui::InputText("##ParticleTexturePath", &texPath);
				ImGui::SameLine();
				if (ImGui::Button("Set texture"))
				{
					for (Particle* p : _particles)
					{
						Texture2D* tex = p->GetTexture();
						if (tex != nullptr)
						{
							p->GetTexture()->Load(texPath);
						}
					}
				}
			}
		}
		else
		{
			if (ImGui::InputFloat4("Particle colour", colour))
			{
				for (Particle* p : _particles)
				{
					p->SetColour(glm::vec4(colour[0], colour[1], colour[2], colour[3]));
					ResetParticle(p);
				}
			}
		}

		// add an input field to change the particle life
		static float particleLife = 1.0f;
		if (ImGui::InputFloat("Particle life", &particleLife))
		{
			for (Particle* p : _particles)
			{
				p->SetMaxLife(particleLife);
				p->SetLife(particleLife);
				ResetParticle(p);
			}
		}
		
		// movement angle
		static float angle = 0.0f;
		if (ImGui::SliderAngle("Movement angle", &angle, 0))
		{
			for (Particle* p : _particles)
			{
				p->SetAngle(angle);
				ResetParticle(p);
			}
		}
		ImGui::SameLine();

		// random direction
		static bool randomDir = true;
		static bool oldRandomDir = randomDir;
		static float angleRange = 0.0f;
		ImGui::Checkbox("Random", &randomDir);
		if (randomDir)
		{
			if (oldRandomDir != randomDir) // oldrandomdir is used so that this is only done once (until it is changed again) to avoid unnecessary looping
			{
				for (Particle* p : _particles)
				{
					p->ToggleRandomDirection(randomDir);
					ResetParticle(p);
				}
			}
			if (ImGui::SliderAngle("Random direction range", &angleRange, 0))
			{
				for (Particle* p : _particles)
				{
					p->SetAngleRange(angleRange);
					ResetParticle(p);
				}
			}
			oldRandomDir = randomDir;
		}

		// change speed
		static float speed = 1.0f;
		if (ImGui::InputFloat("Speed", &speed))
		{
			for (Particle* p : _particles)
			{
				p->SetSpeed(speed);
				ResetParticle(p);
			}
		}

		// scale
		// scale is applied to all particles, so only need to get the first one to see what scale they are currently
		static glm::vec2* pScale = &_particles[0]->GetTransform()->GetScale();
		// copy scale to array for imgui
		static float scale[2] = { pScale->x, pScale->y };
		// create input field and set the scale once edited
		if (ImGui::InputFloat2("Scale", scale))
		{
			for (Particle* p : _particles)
			{
				p->GetTransform()->SetScale(glm::vec2(scale[0], scale[1]));
			}
		}

		// sets whether or not particles will automatically respawn after 'dying'
		static bool* continuous = &_continuous;
		ImGui::Checkbox("Continuous", continuous);
	}
}

void ParticleSystem::CanRespawnParticles(bool toggle)
{
	_canRespawn = toggle;
}

void ParticleSystem::SetParentTransform(Transform* parentTransform)
{
	_pParentTransform = parentTransform;
}

void ParticleSystem::SetShader(string name)
{
	_shaderName = name;
	_pShader = ResourceManager::GetShader(_shaderName);
	_shaderID = _pShader->GetProgramID();
}

void ParticleSystem::ResetParticle(Particle* p)
{
	if (_continuous)
	{
		p->ResetParticle();
	}
}

void ParticleSystem::Fire()
{
	for (Particle* p : _particles)
	{
		p->ResetParticle();
	}
}
