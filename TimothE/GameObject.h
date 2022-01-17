#pragma once
#include <vector>
#include <string>
#include "Component.h"
#include "Transform.h"
#include "UID.h"
#include "TestComponent.h"

class Texture2D;

using std::vector;
using std::string;

enum class ObjectType
{
	Player,
	Enemy,
	NPC,
	PickUp,
	UI
};

class GameObject
{
public:
	GameObject() : _name("New GameObject") {}
	GameObject(string name, ObjectType tag, Texture2D* texture);
	GameObject(string name, ObjectType tag, Texture2D* texture, Transform* transform);
	~GameObject();
	void InitVertexData();

	void Start();
	virtual void Update(float deltaTime);
	void Exit();

	string GetUID() { return _UID; }
	string GetName() { return _name; }

	Component* GetComponent(Component::Types componentType);
	vector<Component*> GetComponents() { return _pComponents; }

	void AddComponent(Component* component, Component::Types type);

	Transform* GetTransform() { return (Transform*)GetComponent(Component::Types::Transform_Type); }
	Texture2D* GetTexture() { return (Texture2D*)GetComponent(Component::Types::Texture_Type); }
	int GetTextureID() { return _textureID; }
	int GetShaderID() { return _shaderID; }

	void LoadTexture(char* path, string mode);
	void SetShader(int id) { _shaderID = id; };
private:
	string _UID;
	string _name;
	ObjectType _tag;
	vector<Component*> _pComponents;

	int _textureID = 0;
	int _shaderID = 0;
};