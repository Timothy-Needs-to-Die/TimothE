#include "GameObject.h"
#include "Texture2D.h"
#include "Stream.h"
#include "ComponentFactory.h"
#include "imgui.h"


GameObject::GameObject(string name, ObjectType tag, Transform* transform) 
	: _name(name), _tag(tag), _pTransform(transform)
{
	_UID = UID::GenerateUID();

	if (_pTransform == nullptr) {
		_pTransform = new Transform();
	}
	AddComponent<Transform>(_pTransform);

	InitVertexData();

	SetDefaultShader();

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
		1.0f, -1.0f, 0.0f,       1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,        1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,       0.0f, 1.0f,

		1.0f, -1.0f, 0.0f,       1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,      0.0f, 0.0f
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
	Texture2D* pTexture = GetComponent<Texture2D>();
	if (pTexture == nullptr)
	{
		pTexture = new Texture2D();
		pTexture->Load(path, mode);
		_textureID = pTexture->GetID();
		AddComponent(pTexture);
		_textureID = pTexture->GetID();
	}
	else
	{
		pTexture->Load(path, mode);
		_textureID = pTexture->GetID();
	}
}

void GameObject::DisplayInEditor()
{
	ImGui::Text(_name.c_str());

	for (auto& comp : _pComponents) {
		comp->DrawEditorUI();
	}

}

void GameObject::SetShader(string vs, string fs)
{
	_pShader = new Shader(vs,fs);
	_shaderID = _pShader->GetProgramID();
	_vsShaderName = vs;
	_fsShaderName = fs;
}

void GameObject::SetShader(Shader* shader)
{
	_pShader = shader;
	_vsShaderName = _pShader->GetVsPath();
	_fsShaderName = _pShader->GetFsPath();
	_shaderID = _pShader->GetProgramID();
}

bool GameObject::SaveState(IStream& stream) const
{
	//Writes name to serialized object
	WriteString(stream, _name);

	WriteString(stream, _UID);

	WriteString(stream, _vsShaderName);
	WriteString(stream, _fsShaderName);


	//Writes number of components
	WriteInt(stream, _pComponents.size());

	for (int i = 0; i < _pComponents.size(); ++i)
	{
		_pComponents[i]->SaveState(stream);
	}

	//TODO: GameObjects need a child system

	return true;
}

bool GameObject::LoadState(IStream& stream)
{
	//Sets our name
	_name = ReadString(stream);

	_UID = ReadString(stream);

	SetShader(ReadString(stream), ReadString(stream));

	//Reserve the amount of components
	int noComponents = ReadInt(stream);

	for (int i = 0; i < noComponents; ++i) {
		Component::Types type = (Component::Types)ReadInt(stream);
		Component::Categories cat = (Component::Categories)ReadInt(stream);


		//Make instance of component
		auto* c = ComponentFactor::GetComponent(type);
		if (c == nullptr) {
			std::cout << "Failed to load Gameobject: " << _name << " Component is null" << std::endl;
			return false;
		}

		//Read instance
		c->LoadState(stream);

		//Set component
		AddComponent(c);
	}

	Texture2D* texture = GetComponent<Texture2D>();
	if (texture != nullptr) {
		_textureID = texture->GetID();
	}

	return true;
}

void GameObject::SetName(string name)
{
	_name = name;
}

void GameObject::SetType(ObjectType tag)
{
	_tag = tag;
}

void GameObject::SetDefaultShader()
{
	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
	SetShader(_pShader);
}

template<typename T>
T* GameObject::GetComponent()
{
	for (auto& comp : _pComponents) {
		if (comp->GetType() == T::GetStaticType()) {
			return (T*)comp;
		}
	}

	return nullptr;
}

template<typename T>
T* GameObject::AddComponent(T* comp)
{
	for (auto& c : _pComponents) {
		if (c->GetType() == comp->GetType())
		{
			return comp;
		}
	}

	_pComponents.push_back(comp);
	return comp;
}
