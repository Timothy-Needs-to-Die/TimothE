#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int count, glm::vec4 colour) : _maxParticles(count)
{
	//Sets the type and category for the component
	SetType(Component::ParticleSystem_Type);
	SetCategory(Component::Graphics_Category);

	SetShader("default");

	_canRespawn = true;

	_parentPos = glm::vec2(0.0f);

	_particles = vector<Particle*>(count);
	for (Particle* p : _particles)
	{
		p = new Particle(1.0f, colour);
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
			p->SetPosition(p->GetPosition() + (p->GetVelocity() * deltaTime));
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
	//TODO: input int for number of particles
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
	p->SetPosition(_parentPos);
	p->SetLife(p->GetMaxLife());
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
