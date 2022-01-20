#pragma once
#include "Shader.h"
#include <vector>
#include <string>
#include "Component.h"
#include "Transform.h"
#include "UID.h"
#include "TestComponent.h"
#include "Serializable.h"
#include "Shader.h"

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

class GameObject : public ISerializable
{
public:
	template<typename T>
	T* GetComponent();
	template<typename T>
	T* AddComponent(T* comp);
	void RemoveComponent(Component* comp);

	GameObject(string name = "New GameObject", ObjectType tag = ObjectType::Player, Transform* transform = nullptr);
	~GameObject();
	void InitVertexData();

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Exit();

	string GetUID() { return _UID; }
	string GetName() { return _name; }
	void SetName(string name);

	ObjectType GetType() { return _tag; }
	void SetType(ObjectType tag);

	void SetDefaultShader();

	vector<Component*> GetComponents() { return _pComponents; }

	Transform* GetTransform() { return _pTransform; }
	int GetTextureID() { return _textureID; }
	int GetShaderID() { return _shaderID; }



	void LoadTexture(char* path, string mode);
	void SetShader(int id) { _shaderID = id; };

	void DisplayInEditor();

	Shader* GetShader() const { return _pShader; }

	void SetShader(string vs, string fs);
	void SetShader(Shader* shader);

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override;
	virtual bool LoadState(IStream& stream) override;
	unsigned int GetVAO() const { return _vao; }
private:
	string _UID;
	string _name;
	ObjectType _tag;
	vector<Component*> _pComponents;

	string _vsShaderName;
	string _fsShaderName;
	Shader* _pShader;

	Transform* _pTransform;

	int _textureID = 0;
	int _shaderID = 0;

	unsigned int _vao;
	unsigned int _vbo;
};
