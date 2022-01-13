#include "GameObject.h"

GameObject::GameObject(string name, ObjectType tag)
{
	_name = name;
	_tag = tag;
	_UID = UID::GenerateUID();
	_pTransform = new Transform();
	Start();
}

GameObject::GameObject(string name, ObjectType tag, Transform* transform)
{
	_name = name;
	_tag = tag;
	_pTransform = transform;
}

GameObject::~GameObject()
{
	Exit();
	for (Component* c : _components)
	{
		delete(c);
	}
	delete(_pTransform);
}

void GameObject::Start()
{
	for (Component* c : _components)
	{
		c->OnStart();
	}
}

void GameObject::Update(float deltaTime)
{
	for (Component* c : _components)
	{
		c->OnUpdate();
	}
}

void GameObject::Exit()
{
	for (Component* c : _components)
	{
		c->OnEnd();
	}
}

Component* GameObject::GetComponent(Component::Types componentType)
{
	for (Component* c : _components)
	{
		if (c->GetType() == componentType)
		{
			return c;
		}
	}
	return nullptr;
}

void GameObject::AddComponent(Component* component)
{
	_components.push_back(component);
}
