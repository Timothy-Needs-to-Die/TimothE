#include "GameObject.h"

GameObject::GameObject()
{
	//_pTransform = new Transform();
}

GameObject::GameObject(Transform* transform)
{
	_pTransform = transform;
}

GameObject::~GameObject()
{
	delete(_pTransform);
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
