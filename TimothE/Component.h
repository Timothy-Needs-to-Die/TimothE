

#pragma once
#include <string>
#include <iostream>
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
#define COMPONENT_CLASS_CATEGOTY(category) virtual int GetCatagory() const override {return category;}
#define COMPONENT_CLASS_TYPE(type) virtual int GetType() const override {return type;}
class Component
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
		Sprite_Type = BIT(7),
	};
	//enums for different catagories of components
	enum Categories {
		None_Catagory = 0,
		Transform_Catagory = BIT(0),
		SoundSystem_Catagory = BIT(1),
		Collisions_Catagory = BIT(2),
		AI_Catagory = BIT(3),
		Graphics_Catagory = BIT(4),
		Debug_Catagory = BIT(5),
	};
	//constructor and destructor calling start and end methods
	Component() {  }
	~Component() {}
	//virtual function for sub class of components
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEnd() = 0;
	//virtual void GetComponent() = 0;
	//gets the component type and catagory 
	virtual int GetCatagory()const = 0 ;
	virtual int GetType()const = 0 ;

	//checks if item is in catagory and type enums
	inline bool IsInCatagory(Categories category) { return GetCatagory() & category; }
	inline bool IsInTypes(Types type) { return GetType() & type; }
protected:
	//variable for type and catagories to be assigned to
	Types type;
	Categories category;
};



