#pragma once
#include "pch.h"

#include "Core/Graphics/Shader.h"
#include "Transform.h"
#include "Component.h"
#include "UID.h"
#include "Serializable.h"
#include "ParticleSystem.h"

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
	GameObject* GetChild(std::string name) 
	{
		for (auto& child : _pChildren) {
			if (child->GetName() == name) {
				return child;
			}
		}
		
		return nullptr;
	};

	////////////////////////
	//Set Ownership States//
	////////////////////////
	void SetParent(GameObject* parent);

	void AddChild(GameObject* newChild);

	void AddedComponent(Component* comp);


	/// <summary>
	/// Checks if this GameObject is a child of the passed in possibleParent GameObject. 
	/// Allows a single level search i.e. Hands are a child of wrists but not of person. 
	/// Or a hierarchical search which would return hands as a child of person
	/// </summary>
	/// <param name="searchHierarchy">Searches this objects parents, grand-parents, great grand parents etc.</param>
	/// <returns></returns>
	bool IsChildOf(GameObject* possibleParent, bool searchHierarchy = true) {
		//If the passed in parent is nullptr, then return. Acts as a fail safe
		if (possibleParent == nullptr) return false;

		//Checks if this object is a child of the possible parent
		if (possibleParent->GetChild(_name) != nullptr) {
			return true;
		}
		
		//If we are not searching the whole hierarchy then return false
		//(the immediate parent was not our parent so we can return false here)
		if (!searchHierarchy) return false;

		//Creates a GameObject* to act as a way to traverse up the hierachy
		GameObject* parentToSearch = possibleParent->GetParent();

		//Stores the game object we want to check against
		GameObject* previousGO = possibleParent;

		//Loops until we have ran out of parents to search
		while (parentToSearch != nullptr) {
			//If the parent to search does contain the previous game object as child. Then we know that the original object is a child
			if (parentToSearch->GetChild(previousGO->GetName()) != nullptr) {
				return true;
			}

			previousGO = parentToSearch;
			parentToSearch = parentToSearch->GetParent();
		}
	}

	//////////////////
	//Get Components//
	//////////////////
	std::vector<Component*> GetComponents() { return _pComponents; }
	Transform* GetTransform() { return _pTransform; }

	////////////////////////
	//Get Child Components//
	////////////////////////
	Component* GetComponentInChild(std::string name, Component::Types type);
	std::vector<Component*> GetComponentsInChild(std::string name);

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
		//TIM_LOG_LOG("IsActive: " << _isActive);

		for (auto& child : _pChildren) {
			child->SetActive(val);
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
	std::vector<GameObject*> _pChildren;

	bool _toBeDestroyed = false;

	virtual void UniqueLogic();
};
