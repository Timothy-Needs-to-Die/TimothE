#pragma once
#include "pch.h"

#include "Core/Graphics/Shader.h"
#include "Transform.h"
#include "Component.h"
#include "UID.h"
#include "Serializable.h"
#include "ParticleSystem.h"
#include "Tag.h"

class Texture2D;
class Scene;

class GameObject : public ISerializable
{
public:
	//////////////////////////
	//Constructor/Destructor//
	//////////////////////////
	GameObject(std::string name, std::string tag = "UNTAGGED");
	~GameObject();

	/////////////
	//Game Loop//
	/////////////
	virtual void Start();
	virtual void Update();
	virtual void Exit();

	/////////////////////
	//Display Functions//
	/////////////////////
	void DisplayInEditor();

	//////////////////////////
	//Get Unique Identifiers//
	//////////////////////////
	std::string GetUID() { return _UID; }
	std::string GetName() { return _name; }
	std::string GetTag() { return _tag; }

	//////////////////////////
	//Set Unique Identifiers//
	//////////////////////////
	void SetName(std::string name);

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


	void AddedComponent(Component* comp);

	//////////////////
	//Get Components//
	//////////////////
	std::vector<Component*> GetComponents() { return _pComponents; }
	Transform* GetTransform() { return _pTransform; }

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
		AddedComponent(comp);
		return comp;
	}

	void RemoveComponent(Component* comp);

	///////////////////////////////
	//Inherited via ISerializable//
	///////////////////////////////
	virtual bool SaveState(IStream& stream) const override;
	virtual bool LoadState(IStream& stream) override;


	virtual void OnTriggerEnter(ColliderBase* other);
	virtual void OnColliderEnter(ColliderBase* other);

	virtual void OnTriggerExit(ColliderBase* other);
	virtual void OnColliderExit(ColliderBase* other);


	bool IsActive() { return _isActive; }
	void SetActive(bool val) {
		_isActive = val;
		TIM_LOG_LOG("IsActive: " << _isActive);
		if (_pChild != nullptr)
		{
			_pChild->SetActive(false);
		}
	}

	bool IsToBeDestroyed() const { return _toBeDestroyed; }
	void SetToBeDestroyed(bool val) { _toBeDestroyed = val; }

private:
	///////////////////////////////////
	//Properties (Unique Identifiers)//
	///////////////////////////////////
	std::string _UID;
	std::string _name;
	std::string _tag;

	bool _isActive = true;

protected:
	//////////////
	//Components//
	//////////////
	std::vector<Component*> _pComponents;
	Transform* _pTransform;

	/////////////
	//Ownership//
	/////////////
	GameObject* _pParent = nullptr;
	GameObject* _pChild = nullptr;

	bool _toBeDestroyed = false;

	virtual void UniqueLogic();
};
