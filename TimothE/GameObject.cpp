#include "GameObject.h"
#include "Texture2D.h"

GameObject::GameObject(string name, ObjectType tag) : _name(name), _tag(tag)
{
	_UID = UID::GenerateUID();
	AddComponent(new Transform(), Component::Types::Transform_Type);
	Start();
}

GameObject::GameObject(string name, ObjectType tag, Transform* transform) : _name(name), _tag(tag)
{
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

void GameObject::RemoveComponent(Component* component)
{
	_pComponents.erase(std::find(_pComponents.begin(), _pComponents.end(), component));
}
