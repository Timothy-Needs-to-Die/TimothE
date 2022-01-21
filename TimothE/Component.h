#pragma once
#include <string>
#include <iostream>
#include "Serializable.h"
#include "Stream.h"

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

//macros to define component type in subclass
#define BIT(x) (1<<x)
class GameObject;

class Component : ISerializable
{
public:
	//setter
	void SetParent(GameObject* newparent) {
		_parentObject = newparent;
	}
	// Getter
	GameObject* Parent() {
		return _parentObject;
	}
	//enum for types of components
	enum Types
	{
		None=0,
		Test_Type = BIT(0),
		Transform_Type = BIT(1),
		Sound_Type = BIT(2),
		Boxcollision_Type = BIT(3),
		CircleCollion_Type = BIT(4),
		PathFinding_Type = BIT(5),
		GOAP_Type = BIT(6),
		Texture_Type = BIT(7),
		Buttom_Type = BIT(8),
	};

	//enums for different catagories of components
	enum Categories {
		None_Category = 0,
		Transform_Category = BIT(0),
		SoundSystem_Category = BIT(1),
		Collisions_Category = BIT(2),
		AI_Category = BIT(3),
		Graphics_Category = BIT(4),
		Debug_Category = BIT(5),
	};

	COMPONENT_STATIC_TYPE(None)

	//constructor and destructor calling start and end methods
	Component(GameObject* pParent) : _parentObject(pParent) { }
	Component() {}
	~Component() {}

	//virtual function for sub class of components
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEnd() = 0;
	//virtual void GetComponent() = 0;

	virtual void DrawEditorUI() = 0;

	//gets the component type and catagory
	Categories GetCategory() const { return _category; }


	Types GetType() const {
		return _type;
	}

	//Set functions
	void SetCategory(Component::Categories category) { _category = category; }
	void SetType(Component::Types type) { _type = type; }

	//checks if item is in catagory and type enums
	inline bool IsInCategory(Categories category) { return GetCategory() & category; }
	inline bool IsInTypes(Types type) { return GetType() & type; }

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override {
		//Write type
		WriteInt(stream, _type);

		//Write category
		WriteInt(stream, _category);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		return true;
	}
protected:
	//variable for type and categories to be assigned to
	Types _type;
	Categories _category;
	GameObject* _parentObject;


};
