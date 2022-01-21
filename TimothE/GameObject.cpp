#include "GameObject.h"
#include "Texture2D.h"
#include "Stream.h"
#include "ComponentFactory.h"
#include "imgui.h"
#include "Console.h"
#include "BoxColliderComponent.h"

GameObject::GameObject(string name, ObjectType tag, Transform* transform) 
	: _name(name), _tag(tag), _pTransform(transform)
{
	_UID = UID::GenerateUID();

	if (_pTransform == nullptr) {
		_pTransform = new Transform(this);
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

void GameObject::LoadTexture(Texture2D* texture)
{
	if (texture == nullptr)
	{
		Console::Print("[Error] Texture is equal too nullptr!");
		return;
	}
	else
	{
		_textureID = texture->GetID();
		AddComponent<Texture2D>(texture);
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
		auto* c = ComponentFactory::GetComponent(type, this);
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

void GameObject::SwapComponents(int index1, int index2)
{
	std::iter_swap(_pComponents.begin() + index1, _pComponents.begin() + index2);
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

void GameObject::RemoveComponent(Component* comp)
{
	_pComponents.erase(std::find(_pComponents.begin(), _pComponents.end(), comp));
	delete comp;
}
