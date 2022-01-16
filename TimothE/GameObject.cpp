#include "GameObject.h"
#include "Texture2D.h"
#include "Stream.h"

GameObject::GameObject(string name, ObjectType tag, Texture2D* texture)
{
	_name = name;
	_tag = tag;
	_UID = UID::GenerateUID();
	_textureID = texture->GetID();
	AddComponent(new Transform(), Component::Types::Transform_Type);
	AddComponent(texture, Component::Types::Texture_Type);
	Start();
}

GameObject::GameObject(string name, ObjectType tag, Texture2D* texture, Transform* transform)
{
	_name = name;
	_tag = tag;
	_UID = UID::GenerateUID();
	AddComponent(transform, Component::Types::Transform_Type);
	AddComponent(texture, Component::Types::Texture_Type);
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

bool GameObject::Write(IStream& stream) const
{
	//TODO: Implement writing and reading component information

	//Writes name to serialized object
	WriteString(stream, _name);

	//Writes number of components
	WriteInt(stream, _pComponents.size());

	//TODO: GameObjects need a child system

	return true;
}

bool GameObject::Read(IStream& stream)
{
	//Sets our name
	_name = ReadString(stream);

	//Reserve the amount of components
	_pComponents.reserve(ReadInt(stream));

	return true;
}

void GameObject::Fixup()
{

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
