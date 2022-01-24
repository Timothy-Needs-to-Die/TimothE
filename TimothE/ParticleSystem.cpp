#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int count, glm::vec4 colour, Texture2D* texture) : _maxParticles(count), _particleColour(colour), _pTexture(texture)
{
	//Sets the type and category for the component
	SetType(Component::ParticleSystem_Type);
	SetCategory(Component::Graphics_Category);

	SetShader("default");

	_canRespawn = true;

	_parentPos = glm::vec2(0.0f);

	_particleLife = 1.0f;
	for (int i = 0; i < count; i++)
	{
		Particle* p = new Particle(_particleLife, colour, _pTexture);
		_particles.push_back(p);
		RespawnParticle(p);
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
			// update position
			glm::vec2 newPos = p->GetTransform()->GetPosition() + (p->GetVelocity() * deltaTime);
			Transform* t = p->GetTransform();
			t->SetPosition(newPos.x, newPos.y);
			p->SetTransform(t);
			//p->SetPosition(p->GetPosition() + (p->GetVelocity() * deltaTime));
		}
		else // life lower than 0, particle no longer alive
		{
			if (_canRespawn)
			{
				RespawnParticle(p);
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

	// create input field to change max amount of particles
	static int* maxparticles = &_maxParticles;
	if (ImGui::InputInt("Max particles", maxparticles))
	{
		// if the value is changed, change the number of particles in vector
		int dif = _maxParticles - _particles.size();
		if (_maxParticles > _particles.size())
		{
			for (int i = 0; i < dif; i++)
			{
				// add new particles
				_particles.push_back(new Particle(_particleLife, _particleColour, _pTexture));
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
	}

	//TODO: input float4 for colour
	//TODO: input float for particle life
}

void ParticleSystem::CanRespawnParticles(bool toggle)
{
	_canRespawn = toggle;
}

void ParticleSystem::SetParentPos(glm::vec2 newParent)
{
	_parentPos = newParent;
}

void ParticleSystem::SetShader(string name)
{
	_shaderName = name;
	_pShader = ResourceManager::GetShader(_shaderName);
	_shaderID = _pShader->GetProgramID();
}

void ParticleSystem::RespawnParticle(Particle* p)
{
	// reset position and life
	Transform* t = p->GetTransform();
	t->SetPosition(_parentPos.x, _parentPos.y);
	p->SetTransform(t);
	p->SetLife(p->GetMaxLife());
}

Particle::Particle(float life, glm::vec4 colour, Texture2D* texture) : _position(0.0f), _velocity(0.0f), _colour(colour), _life(life), _maxLife(life), _pTexture(texture)
{
	_pTransform = new Transform(nullptr);
	InitVertexData();
}

void Particle::InitVertexData()
{
	float vertexData[]{
		//position               //texture coords
		1.0f, -1.0f, 0.0f,       1.0f, 0.0f,     //bottom right
		1.0f, 1.0f, 0.0f,        1.0f, 1.0f,     //top right
		-1.0f, 1.0f, 0.0f,       0.0f, 1.0f,     //top left

		1.0f, -1.0f, 0.0f,       1.0f, 0.0f,     //bottom right
		-1.0f, 1.0f, 0.0f,       0.0f, 1.0f,     //top left
		-1.0f, -1.0f, 0.0f,      0.0f, 0.0f      //bottom left
	};

	//VAO
	glGenVertexArrays(1, &_vao);

	//VBO
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	// This will identify our vertex buffer
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(float),                  // stride
		(void*)(3 * sizeof(float))          // array buffer offset
	);
	glEnableVertexAttribArray(1);
}

void Particle::SetTransform(Transform* newTransform)
{
	_pTransform = newTransform;
}
