#pragma once
#include <vector>
#include <string>
#include "Component.h"
#include "Transform.h"
#include "UID.h"
#include "TestComponent.h"
#include "Serializable.h"

class Texture2D;

using std::vector;
using std::string;

enum class ObjectType
{
	Player,
	Enemy,
	NPC,
	PickUp
};

class GameObject : public ISerializable
{
public:
	GameObject() {}
	GameObject(string name) : _name(name) {}
	GameObject(string name, ObjectType tag, Texture2D* texture);
	GameObject(string name, ObjectType tag, Texture2D* texture, Transform* transform);
	~GameObject();

	void Start();
	void Update(float deltaTime);
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

	// Inherited via ISerializable
	virtual bool Write(IStream& stream) const override;
	virtual bool Read(IStream& stream) override;
	virtual void Fixup() override;
private:
	string _UID;
	string _name;
	ObjectType _tag;
	vector<Component*> _pComponents;

	int _textureID = 0;
	int _shaderID = 0;


};