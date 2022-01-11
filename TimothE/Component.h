

#pragma once
#include "TestComponent.h"
#include <string>
#include <iostream>


/// <summary>
/// Component class is an attachable class for gameobjects that can run start, update, end methods
/// Get component method also allows the game object to call functions within the component
/// test code below will run a test component
/// Component<TestComponent>* comp = new Component<TestComponent>();
/// comp->GetComponent().Test();
/// comp->OnUpdate();
/// delete comp;
/// </summary>
/// <typeparam name="T"></typeparam>

template <typename T>
class Component
{
private:
	T component;
	std::string name;
	std::string catagory;
public:
	////enum for component types
	//enum ComponentType {
	//	Test,
	//	Transform,
	//	Sprite,
	//	Sound,
	//	CollisionBox,
	//	CollisionCircle,
	//};
	////enum for component catagories
	//enum ComponentCatagory {
	//	Test,
	//	Transform,
	//	Graphics,
	//	Sound,
	//	AI,
	//	Collisions
	//};
	//constructor and destructor calling start and end methods
	Component() {  OnStart(); }
	~Component() { OnEnd(); }

	//returns component type
	T GetComponent() {
		return component;
	}
	//on component start 
	void OnStart() {
		component.OnStart();
	}
	//update component
	void OnUpdate() {
		component.OnUpdate();
	}
	//end component
	void OnEnd() {
		component.OnEnd();
	}
};



