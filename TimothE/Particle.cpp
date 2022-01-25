#include "Particle.h"

Particle::Particle(float life, glm::vec4 colour, Texture2D* texture, Transform* parentTransform) : _velocity(0.0f), _colour(colour), _life(life), _maxLife(life), _pTexture(texture), _pParentTransform(parentTransform)
{
	_pTransform = new Transform(nullptr);
	InitVertexData();
}

void Particle::Update(float deltaTime)
{
	glm::vec2 newPos = _pTransform->GetPosition() + glm::vec2(10);// (_velocity * deltaTime);
	_pTransform->SetPosition(newPos.x, newPos.y);
	glm::mat4 mat = _pTransform->GetTransformMatrix();
	//
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

void Particle::ResetParticle()
{
	_pTransform->SetPosition(_pParentTransform->GetPosition().x, _pParentTransform->GetPosition().y);
	_life = _maxLife;
}

void Particle::SetTransform(Transform* newTransform)
{
	_pTransform = newTransform;
}

void Particle::SetParentTransform(Transform* parentTransform)
{
	parentTransform = parentTransform;
}
