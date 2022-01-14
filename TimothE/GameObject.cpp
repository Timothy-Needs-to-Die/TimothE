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
	Start();
}

GameObject::GameObject(string name, ObjectType tag, Transform* transform)
{
	_name = name;
	_tag = tag;
	_UID = UID::GenerateUID();
	AddComponent(transform, Component::Types::Transform_Type);
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
