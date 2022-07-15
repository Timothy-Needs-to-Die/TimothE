#include "pch.h"
#include "TestComponent.h"

TestComponent::TestComponent(GameObject* pParent) : Component(pParent)
{
	SetType(Component::Types::Test_Type);
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



