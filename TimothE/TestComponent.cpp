#include "TestComponent.h"
#include "GameObject.h"

#include <iostream>


TestComponent::TestComponent(GameObject* parentObject) : Component()
{
	_parentObject = parentObject;
	//calls method on creation
	OnStart();
}

TestComponent::~TestComponent()
{
	
	//calls method on destrution
	OnEnd();
}

//start
void TestComponent::OnStart()
{

}

//update
void TestComponent::OnUpdate()
{

}

//end
void TestComponent::OnEnd()
{

}

//test function for component
void TestComponent::Test(int x,int y)
{

}

void TestComponent::DrawEditorUI()
{

}



