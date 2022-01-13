#pragma once
#include <vector>
#include <string>
#include "Component.h"
#include "Transform.h"
#include "UID.h"
#include "TestComponent.h"

using std::vector;
using std::string;

enum class ObjectType
{
	Player,
	Enemy,
	NPC,
	PickUp
};

class GameObject
{
public:
	GameObject(string name, ObjectType tag);
	GameObject(string name, ObjectType tag, Transform* transform);
	~GameObject();

	void Start();
	void Update(float deltaTime);
	void Exit();

	string GetUID() { return _UID; }
	string GetName() { return _name; }
	Component* GetComponent(Component::Types componentType);
	vector<Component*> GetComponents() { return _components; }
	Transform* GetTransform() { return _pTransform; }

	void AddComponent(Component* component);
private:
	string _UID;
	string _name;
	ObjectType _tag;
	vector<Component*> _components;
	Transform* _pTransform;
};