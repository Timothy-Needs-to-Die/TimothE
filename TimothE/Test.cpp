#include "Test.h"

#include <iostream>


TestComponent::TestComponent(GameObject* parentObject) : Component()
{
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
	_parentObject->GetTransform()->SetPosition(5,7);
	std::cout << _parentObject->GetTransform()->GetPosition()->_x << std::endl;
	std::cout << _parentObject->GetTransform()->GetPosition()->_y << std::endl;
}

//update
void TestComponent::OnUpdate()
{
	std::cout << "test update" << std::endl;
}

//end
void TestComponent::OnEnd()
{
	std::cout << "test end" << std::endl;
}

//test function for component
void TestComponent::Test(int x,int y)
{
	std::cout << "test func:" << x*y << std::endl;
}



