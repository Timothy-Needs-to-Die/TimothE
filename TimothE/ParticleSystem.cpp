#include "pch.h"
#include "ParticleSystem.h"
#include "misc/cpp/imgui_stdlib.h"
#include "Time.h"
#include "Texture2D.h"

ParticleSystem::ParticleSystem(int count, glm::vec4 colour, Texture2D* texture, Transform* parentTransform) : _maxParticles(count), _particleColour(colour), _pTexture(texture), _pParentTransform(parentTransform), _particleLife(1.0f)
{
	//Sets the type and category for the component
	SetType(Component::ParticleSystem_Type);

	SetShader("default");

	// creatingparticles enables the process of spawning new particles after a delay to make them come out at a constant rate
	_creatingParticles = false;
	// spawndelay is the delay between enabling new particles
	_spawnDelay = _particleLife / _maxParticles;

	CreateParticles();
}

ParticleSystem::~ParticleSystem()
{
	
}

void ParticleSystem::OnStart()
{
}

void ParticleSystem::OnUpdate()
{
	if (_creatingParticles)
	{
		static float timer = 0.0f;
		timer += Time::GetDeltaTime();
		if (timer >= _spawnDelay)
		{
			static int creatingIndex = 0;
			if (creatingIndex < _maxParticles)
			{
				_particles[creatingIndex]->SetCanRespawn(true);
				_particles[creatingIndex]->ResetParticle();
				creatingIndex++;
			}
			else
			{
				_creatingParticles = false;
				for (Particle* p : _particles)
				{
					p->SetCanRespawn(true);
				}
				creatingIndex = 0;
			}

			timer = 0.0f;
		}
	}

	for (Particle* p : _particles)
	{
		// reduce particle life by deltatime
		p->SetLife(p->GetLife() - Time::GetDeltaTime());
		if (p->GetLife() > 0.0f) // if life greater than 0, still alive so update
		{
			p->SetParentTransform(_pParentTransform);
			p->Update();

			//p->SetPosition(p->GetPosition() + (p->GetVelocity() * deltaTime));
		}
		else // life lower than 0, particle no longer alive
		{
			if (p->GetCanRespawn())
			{
				p->ResetParticle();
			}
		}
	}
}

void ParticleSystem::OnEnd()
{
}

void ParticleSystem::DrawEditorUI()
{
	if (ImGui::CollapsingHeader("Particle System"))
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

			_creatingParticles = true;
			for (Particle* p : _particles)
			{
				RespawnParticle(p, false);
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
				if (ImGui::Button("Set texture##ParticleSystem"))
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
			static float oldWidth = ImGui::CalcItemWidth();
			if (ImGui::CollapsingHeader("Particle colour"))
			{
				ImGui::PushItemWidth(200);
				if (ImGui::ColorPicker4("Particle colour", colour))
				{
					_creatingParticles = true;
					for (Particle* p : _particles)
					{
						p->SetColour(glm::vec4(colour[0], colour[1], colour[2], colour[3]));
						RespawnParticle(p, false);
					}
				}
			}
			ImGui::PushItemWidth(oldWidth);
		}

		// add an input field to change the particle life
		static float particleLife = 1.0f;
		if (ImGui::InputFloat("Particle life", &particleLife))
		{
			_creatingParticles = true;
			for (Particle* p : _particles)
			{
				p->SetMaxLife(particleLife);
				p->SetLife(particleLife);
				RespawnParticle(p, false);
			}
		}
		
		// movement angle
		static float angle;
		if (ImGui::SliderAngle("Movement angle", &angle, 0))
		{
			_creatingParticles = true;
			for (Particle* p : _particles)
			{
				p->SetAngle(angle);
				RespawnParticle(p, false);
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
				_creatingParticles = true;
				for (Particle* p : _particles)
				{
					p->ToggleRandomDirection(randomDir);
					RespawnParticle(p, false);
				}
			}
			if (ImGui::SliderAngle("Random direction range", &angleRange, 0))
			{
				_creatingParticles = true;
				for (Particle* p : _particles)
				{
					p->SetAngleRange(angleRange);
					RespawnParticle(p, false);
				}
			}
			oldRandomDir = randomDir;
		}

		// change speed
		static float speed = 1.0f;
		if (ImGui::InputFloat("Speed", &speed))
		{
			_creatingParticles = true;
			for (Particle* p : _particles)
			{
				p->SetSpeed(speed);
				RespawnParticle(p, false);
			}
		}

		// scale
		// scale is applied to all particles, so only need to get the first one to see what scale they are currently
		static glm::vec2* pScale = &_particles[0]->GetTransform()->GetScale();
		// copy scale to array for imgui
		static float scale[2] = { pScale->x, pScale->y };
		// create input field and set the scale once edited
		if (ImGui::InputFloat2("Scale##ParticleSystem", scale))
		{
			for (Particle* p : _particles)
			{
				p->GetTransform()->SetScale(glm::vec2(scale[0], scale[1]));
			}
		}

		// start and stop buttons
		if (ImGui::Button("Constant"))
		{
			StartConstant();
		}
		ImGui::SameLine();
		if (ImGui::Button("Burst"))
		{
			Burst();
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			Stop();
		}
	}
}

void ParticleSystem::SetCanRespawnParticles(bool toggle)
{
	for (Particle* p : _particles)
	{
		p->SetCanRespawn(toggle);
	}
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

/// <summary> resets the particle. if set to inactive will disable respawns and life to -1 </summary>
void ParticleSystem::RespawnParticle(Particle* p, bool active)
{
	if (p->GetCanRespawn())
	{
		p->ResetParticle();
		if (!active)
		{
			// set to disabled (life < 0 makes it not render + setting to not respawn makes it stay like that)
			p->SetLife(-1.0f);
			p->SetCanRespawn(false);
		}
	}
}

void ParticleSystem::StartConstant()
{
	_creatingParticles = true;
	for (Particle* p : _particles)
	{
		RespawnParticle(p, false);
	}
}

void ParticleSystem::Burst()
{
	_creatingParticles = false;
	SetActive(true);
}

void ParticleSystem::Stop()
{
	SetActive(false);
}

void ParticleSystem::SetActive(bool active)
{
	// set active, which enables or disables respawning
	for (Particle* p : _particles)
	{
		p->ResetParticle();
		p->SetCanRespawn(active);
		if (!active)
		{
			p->SetLife(-1.0f);
		}
	}
}

void ParticleSystem::CreateParticles()
{
	for (int i = 0; i < _maxParticles; i++)
	{
		// create new particle
		Particle* p = new Particle(_particleLife, _particleColour, _pTexture, _pParentTransform);
		// add to vector
		_particles.push_back(p);
		RespawnParticle(p, false);
	}
}
