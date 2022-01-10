#pragma once
#include <vector>
#include <string>
#include "Component.h"
#include "Transform.h"

using std::vector;
using std::string;

class GameObject
{
public:
	GameObject();
	GameObject(Transform* transform);
	~GameObject();

	Component* GetComponent(string name);
	vector<Component*> GetComponents() { return _components; }
	Transform* GetTransform() { return _pTransform; }
private:
	vector<Component*> _components;
	Transform* _pTransform;
};