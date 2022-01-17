#include "GameObject.h"
#include "Texture2D.h"

GameObject::GameObject(string name, ObjectType tag, Texture2D* texture)
{
	_name = name;
	_tag = tag;
	_UID = UID::GenerateUID();
	_textureID = texture->GetID();
	AddComponent(new Transform(), Component::Types::Transform_Type);
	AddComponent(texture, Component::Types::Texture_Type);
	InitVertexData();
	Start();
}

GameObject::GameObject(string name, ObjectType tag, Texture2D* texture, Transform* transform)
{
	_name = name;
	_tag = tag;
	_UID = UID::GenerateUID();
	AddComponent(transform, Component::Types::Transform_Type);
	AddComponent(texture, Component::Types::Texture_Type);
	InitVertexData();

	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
	_shaderID = _pShader->GetProgramID();
	

	Start();
}

GameObject::~GameObject()
{
	Exit();
	for (Component* c : _pComponents)
	{
		delete(c);
	}
}

void GameObject::InitVertexData()
{
	float vertexData[]{
		//position               //texture coords
		0.5f, -0.5f, 0.0f,       1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,        1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,       0.0f, 1.0f,

		0.5f, -0.5f, 0.0f,       1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,       0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,      0.0f, 0.0f
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

	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); //apparently wasnt needed???? -Lucy
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

void GameObject::Start()
{
	for (Component* c : _pComponents)
	{
		c->OnStart();
	}
}

void GameObject::Update(float deltaTime)
{
	for (Component* c : _pComponents)
	{
		c->OnUpdate();
	}
}

void GameObject::Exit()
{
	for (Component* c : _pComponents)
	{
		c->OnEnd();
	}
}

void GameObject::LoadTexture(char* path, string mode)
{
	if (GetTexture() == nullptr)
	{
		Texture2D* texture = new Texture2D();
		texture->Load(path, mode);
		_textureID = texture->GetID();
		AddComponent(texture, Component::Types::Texture_Type);

		return;
	}
	else
	{
		GetTexture()->Load(path, mode);
	}
}

Component* GameObject::GetComponent(Component::Types componentType)
{
	for (Component* c : _pComponents)
	{
		if (c->GetType() == componentType)
		{
			return c;
		}
	}
	return nullptr;
}

void GameObject::AddComponent(Component* component, Component::Types type)
{
	component->SetType(type);
	_pComponents.push_back(component);
}
