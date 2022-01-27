#include "Particle.h"
#include <random>

Particle::Particle(float life, glm::vec4 colour, Texture2D* texture, Transform* parentTransform) : _movementVec(0.0f), _colour(colour), _currentLife(life), _maxLife(life), _pTexture(texture), _pParentTransform(parentTransform), _speed(1.0f), _useRandomDirection(true), _angleRange(10.0f), _angle(0.0f)
{
	_pTransform = new Transform(nullptr);
	InitVertexData();
}

void Particle::Update(float deltaTime)
{
	glm::vec2 newPos = _pTransform->GetPosition() + (_movementVec * deltaTime);
	_pTransform->SetPosition(newPos.x, newPos.y);
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

void Particle::SetLife(float newLife)
{
	_currentLife = newLife;
}

void Particle::SetMaxLife(float life)
{
	_maxLife = life;
}

void Particle::ResetParticle()
{
	_pTransform->SetPosition(_pParentTransform->GetPosition().x, _pParentTransform->GetPosition().y);
	_currentLife = _maxLife;

	// create a random angle in range
	float randAngle = (((float)rand() / RAND_MAX) * _angleRange);
	float angle = _angle + (randAngle - (_angleRange * 0.5f));
	SetAngle(angle);
}

void Particle::SetVelocity(glm::vec2 newVelocity)
{
	_movementVec = newVelocity;
}

void Particle::SetColour(glm::vec4 newColour)
{
	_colour = newColour;
}

void Particle::SetTransform(Transform* newTransform)
{
	_pTransform = newTransform;
}

void Particle::SetParentTransform(Transform* parentTransform)
{
	parentTransform = parentTransform;
}

void Particle::SetAngle(float angle)
{
	_angle = angle;
	glm::vec2 vec;
	vec.x = cos(angle);
	vec.y = sin(angle);
	vec = glm::normalize(vec);
	_movementVec = vec * _speed;
}

void Particle::ToggleRandomDirection(bool useRand)
{
	_useRandomDirection = useRand;
}

void Particle::SetAngleRange(float range)
{
	_angleRange = range;
}

void Particle::SetSpeed(float speed)
{
	_speed = speed;

	glm::vec2 vec = glm::normalize(_movementVec);
	_movementVec = vec * _speed;
}
