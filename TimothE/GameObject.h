#pragma once
#include "pch.h"

#include "Shader.h"
#include "Transform.h"
#include "Component.h"
#include "UID.h"
#include "Serializable.h"
#include "Shader.h"
#include "BoxColliderComponent.h"

class Texture2D;

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
	T* GetComponent()
	{
		for (auto& comp : _pComponents) {
			if (comp->GetType() == T::GetStaticType()) {
				return (T*)comp;
			}
		}

		return nullptr;
	}
	template<typename T>
	T* AddComponent(T* comp)
	{
		for (auto& c : _pComponents) {
			if (c->GetType() == comp->GetType())
			{
				return comp;
			}
		}

		_pComponents.push_back(comp);
		return comp;
	}
	void RemoveComponent(Component* comp);

	GameObject(string name = "New GameObject", ObjectType tag = ObjectType::Player, Transform* transform = nullptr);
	~GameObject();
	void InitVertexData();

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Exit();

	std::string GetUID() { return _UID; }
	std::string GetName() { return _name; }
	void SetName(std::string name);

	ObjectType GetType() { return _tag; }
	void SetType(ObjectType tag);

	vector<Component*> GetComponents() { return _pComponents; }

	Transform* GetTransform() { return _pTransform; }
	int GetTextureID() { return _textureID; }
	int GetShaderID() { return _shaderID; }

	void LoadTexture(Texture2D* texture);
	void SetShader(int id) { _shaderID = id; };

	void DisplayInEditor();

	Shader* GetShader() const { return _pShader; }

	void SetShader(std::string name);

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override;
	virtual bool LoadState(IStream& stream) override;
	unsigned int GetVAO() const { return _vao; }

	void SwapComponents(int index1, int index2);
private:
	//properties
	std::string _UID;
	std::string _name;
	ObjectType _tag;

	//components
	vector<Component*> _pComponents;

	//shaders
	Shader* _pShader;
	std::string _shaderName;

	Transform* _pTransform;

	int _textureID = 0;
	int _shaderID = 0;

	unsigned int _vao;
	unsigned int _vbo;
};
