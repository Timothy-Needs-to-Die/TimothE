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
	/*for (Component* c : _components)
	{
		c->Start();
	}*/
}

void GameObject::Update(float deltaTime)
{
	/*for (Component* c : _components)
	{
		c->Update();
	}*/
}

void GameObject::Exit()
{
	/*for (Component* c : _components)
	{
		c->Exit();
	}*/
}

Component* GameObject::GetComponent(string name)
{
	/*for (Component* c : _components)
	{
		if (c->GetName() == name)
		{
			return c;
		}
	}*/
	return nullptr;
}
Component* GameObject::GetComponent(string ID)
{
	/*for (Component* c : _components)
	{
		if (c->GetUID() == ID)
		{
			return c;
		}
	}*/
	return nullptr;
}

void GameObject::AddComponent(Component* component)
{
	_components.push_back(component);
}
