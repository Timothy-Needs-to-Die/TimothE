#pragma once
#include "pch.h"

#include "Serializable.h"
#include "Stream.h"
#include "imgui.h"

class GameObject;

/// <summary>
///
///COMPONENT_STATIC_TYPE(Texture_Type)
///TestComponent();
///~TestComponent();
///void OnStart() override;
///void OnUpdate() override;
///void OnEnd() override;
/// </summary>
/// <returns></returns>

#define COMPONENT_STATIC_TYPE(type) static Types GetStaticType() {return Types::##type; }

class GameObject;

class Component
{
public:
	//enum for types of components
	enum Types
	{
		None = 0,
		Test_Type,
		Transform_Type,
		Sound_Type,
		Boxcollision_Type,
		CircleCollion_Type,
		PathFinding_Type,
		GOAP_Type,
		Texture_Type,
		Button_Type,
		Text_Type,
		ParticleSystem_Type,
		TileMap_Type,
		Camera_Type,
		Collider,
		PlayerInput,
		Movement,
		SpriteType,
		Trader_Type,
		Fighter_Type,
		Health_Type,
		ResourceNode_Type,
		StructureFighter_Type,
		AIControllerType,
		AIMovement_Type,
		DestroyAfterSeconds_Type,
		Pathfinding,
		Weapon_Type,
		PlayerUI_Type
	};

	COMPONENT_STATIC_TYPE(None)

	//constructor and destructor calling start and end methods
	Component(GameObject* pOwner) : _pOwner(pOwner), _type(None) { }
	Component() = default;
	~Component() 
	{
		_pOwner = nullptr;
	}

	//virtual function for sub class of components
	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnEnd() {}
	//virtual void GetComponent() = 0;

	virtual void DrawEditorUI() {
		if (ImGui::Checkbox("IsEnabled", _editorIsEnabled))
		{
			std::cout << "IsEnabled = " << *_editorIsEnabled << std::endl;
			SetEnabled(*_editorIsEnabled);
		}
	}

	//gets the component type and category
	Types GetType() const { return _type; }

	//Set functions
	void SetType(Component::Types type) { _type = type; }

	//setter
	void SetOwner(GameObject* parent) { _pOwner = parent; }
	// Getter
	GameObject* GetOwner() { return _pOwner; }

	//checks if item is in category and type enums
	inline bool IsInTypes(Types type) { return GetType() & type; }


	virtual void OnTriggerEnter(class ColliderBase* other) {}
	virtual void OnCollisionEnter(class ColliderBase* other) {}

	virtual void OnTriggerExit(class ColliderBase* other) {}
	virtual void OnCollisionExit(class ColliderBase* other) {}

	// IsEnabled Get & Set
	bool IsEnabled() { return _isEnabled; }
	void SetEnabled(bool state) { _isEnabled = state; }
protected:
	//variable for type and categories to be assigned to
	Types _type;
	GameObject* _pOwner;

	bool _isEnabled = true;
	bool* _editorIsEnabled = &_isEnabled;
};
