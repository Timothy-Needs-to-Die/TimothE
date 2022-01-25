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
class Scene;

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
	//////////////////////////
	//Constructor/Destructor//
	//////////////////////////
	GameObject(std::string name = "New GameObject", ObjectType tag = ObjectType::Player, Transform* transform = nullptr);
	~GameObject();

	/////////////
	//Game Loop//
	/////////////
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Exit();

public:
	///////////////////////
	//Data Initialisation//
	///////////////////////
	void InitVertexData();
	void LoadTexture(Texture2D* texture);

	/////////////////////
	//Display Functions//
	/////////////////////
	void DisplayInEditor();

public:
	//////////////////////////
	//Get Unique Identifiers//
	//////////////////////////
	std::string GetUID() { return _UID; }
	std::string GetName() { return _name; }
	ObjectType GetType() { return _tag; }
	int GetTextureID() { return _textureID; }
	int GetShaderID() { return _shaderID; }

	//////////////////////////
	//Set Unique Identifiers//
	//////////////////////////
	void SetName(std::string name);
	void SetType(ObjectType tag);

	////////////////////////
	//Get Ownership States//
	////////////////////////
	GameObject* GetParent() { return _pParent; };
	GameObject* GetChild() { return _pChild; };

	////////////////////////
	//Set Ownership States//
	////////////////////////
	void SetParent(GameObject* parent);
	void SetChild(GameObject* child);

public:
	//////////////////
	//Get Components//
	//////////////////
	std::vector<Component*> GetComponents() { return _pComponents; }
	Transform* GetTransform() { return _pTransform; }
	Shader* GetShader() const { return _pShader; }

	////////////////////////
	//Get Child Components//
	////////////////////////
	Component* GetComponentInChild(Component::Types type);
	std::vector<Component*> GetComponentsInChild();

	/////////////////////////
	//Get Parent Components//
	/////////////////////////
	Component* GetComponentInParent(Component::Types type);
	std::vector<Component*> GetComponentsInParent();

	///////////////////
	//Swap Components//
	///////////////////
	void SwapComponents(int index1, int index2);

	//////////////////
	//Set Components//
	//////////////////
	void SetShader(int id) { _shaderID = id; };
	void SetShader(std::string name);

	////////////////////////////
	//Component Get/Add/Remove//
	////////////////////////////
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
		//Scene::AddedComponentHandler(this, comp);
		return comp;
	}

	void RemoveComponent(Component* comp);

public:
	///////////////////////////////
	//Inherited via ISerializable//
	///////////////////////////////
	virtual bool SaveState(IStream& stream) const override;
	virtual bool LoadState(IStream& stream) override;
	unsigned int GetVAO() const { return _vao; }
private:
	///////////////////////////////////
	//Properties (Unique Identifiers)//
	///////////////////////////////////
	std::string _UID;
	std::string _name;
	ObjectType _tag;
	int _textureID = 0;
	int _shaderID = 0;

	/////////////
	//Ownership//
	/////////////
	GameObject* _pParent = nullptr;
	GameObject* _pChild = nullptr;

	//////////////
	//Components//
	//////////////
	std::vector<Component*> _pComponents;
	Transform* _pTransform;

	///////////
	//Shaders//
	///////////
	Shader* _pShader;
	std::string _shaderName;

	///////////
	//Buffers//
	///////////
	unsigned int _vao;
	unsigned int _vbo;
};
