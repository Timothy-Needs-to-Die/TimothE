#include "GameObject.h"
#include "Texture2D.h"
#include "Stream.h"
#include "ComponentFactory.h"
#include "imgui.h"


GameObject::GameObject(string name, ObjectType tag) : _name(name), _tag(tag)
{
	_UID = UID::GenerateUID();
	AddComponent(new Transform(), Component::Types::Transform_Type);
	InitVertexData();

	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
	_shaderID = _pShader->GetProgramID();

	Start();
}

GameObject::GameObject(string name, ObjectType tag, Transform* transform) : _name(name), _tag(tag)
{
	_UID = UID::GenerateUID();
	AddComponent(transform, Component::Types::Transform_Type);

	AddComponent(new Texture2D(), Component::Types::Texture_Type);
	InitVertexData();

	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
	_shaderID = _pShader->GetProgramID();

	Start();
}

GameObject::GameObject() : _name("New GameObject")
{
	_UID = UID::GenerateUID();
	Transform* pTransform = new Transform();
	AddComponent(pTransform, Component::Transform_Type);
	InitVertexData();

	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
	_shaderID = _pShader->GetProgramID();

	Start();
}

GameObject::GameObject(string name) : _name(name)
{
	Transform* pTransform = new Transform();
	AddComponent(pTransform, Component::Transform_Type);
	InitVertexData();

	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
	_shaderID = _pShader->GetProgramID();

	Start();
}

GameObject::GameObject(string name, ObjectType tag, Texture2D* texture) : _name(name), _tag(tag)
{
	_UID = UID::GenerateUID();
	Transform* pTransform = new Transform();
	AddComponent(pTransform, Component::Transform_Type);
	AddComponent(texture, Component::Texture_Type);
	InitVertexData();

	_pShader = new Shader("VertexShader.vert", "FragmentShader.frag");
	_shaderID = _pShader->GetProgramID();

	Start();
}

GameObject::GameObject(string name, ObjectType tag, Texture2D* texture, Transform* transform) : _name(name), _tag(tag)
{
	_UID = UID::GenerateUID();
	AddComponent(transform, Component::Transform_Type);
	AddComponent(texture, Component::Texture_Type);
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
		_textureID = texture->GetID();
	}
	else
	{
		GetTexture()->Load(path, mode);
		_textureID = GetTexture()->GetID();
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

bool GameObject::Write(IStream& stream) const
{
	//TODO: Implement writing and reading component information

	//Writes name to serialized object
	WriteString(stream, _name);

	WriteString(stream, _UID);

	WriteString(stream, _vsShaderName);
	WriteString(stream, _fsShaderName);


	//Writes number of components
	WriteInt(stream, _pComponents.size());

	for (int i = 0; i < _pComponents.size(); ++i)
	{
		_pComponents[i]->Write(stream);
	}

	//TODO: GameObjects need a child system

	return true;
}

bool GameObject::Read(IStream& stream)
{
	//Sets our name
	_name = ReadString(stream);

	_UID = ReadString(stream);

	SetShader(ReadString(stream), ReadString(stream));

	//Reserve the amount of components
	int noComponents = ReadInt(stream);
	//_pComponents.reserve(noComponents);

	for (int i = 0; i < noComponents; ++i) {
		Component::Types type = (Component::Types)ReadInt(stream);
		Component::Categories cat = (Component::Categories)ReadInt(stream);


		//Make instance of component
		Component* c = ComponentFactor::GetComponent(type);
		if (c == nullptr) {
			std::cout << "Failed to load Gameobject: " << _name << " Component is null" << std::endl;
			return false;
		}

		//Read instance
		c->Read(stream);

		//Set component

		AddComponent(c, c->GetType());
		//_pComponents[i] = c;
	}

	Texture2D* texture = (Texture2D*)GetComponent(Component::Texture_Type);
	if (texture != nullptr) {
		_textureID = texture->GetID();
	}

	return true;
}

void GameObject::Fixup()
{

}

void GameObject::SetName(string name)
{
	_name = name;
}

void GameObject::SetType(ObjectType tag)
{
	_tag = tag;
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
