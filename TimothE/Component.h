#pragma once

#include <string>
#include <iostream>
#include "Serializable.h"
#include "Stream.h"

/// <summary>
/// 
/// COMPONENT_CLASS_CATEGOTY(Debug);
///COMPONENT_CLASS_TYPE(Test1);
///TestComponent();
///~TestComponent();
///void OnStart() override;
///void OnUpdate() override;
///void OnEnd() override;
/// </summary>
/// <returns></returns>


//macros to define component type in subclass
#define BIT(x) (1<<x)
class Component : ISerializable
{
public:
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

	//constructor and destructor calling start and end methods
	Component() { }
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
	virtual bool Write(IStream& stream) const override {
		//Write type
		WriteInt(stream, _type);

		//Write category
		WriteInt(stream, _category);

		return true;
	}
	virtual bool Read(IStream& stream) override {
		//Read type
		//_type = (Types)ReadInt(stream);

		//Read Category //Not sure if this will work? Testing required
		//_category = (Categories)ReadInt(stream);


		return true;
	}
	virtual void Fixup() override {

	}
protected:
	//variable for type and catagories to be assigned to
	Types _type;
	Categories _category;


};



