#include "Test.h"
#include <iostream>

//TestComponent::TestComponent()
//{
//	std::cout << "construct" << std::endl;
//}

void TestComponent::OnStart()
{
	std::cout << "test start" << std::endl;
	Test(5,6);
}

void TestComponent::OnUpdate()
{
	std::cout << "test update" << std::endl;
}

void TestComponent::OnEnd()
{
	std::cout << "test end" << std::endl;
}

void TestComponent::Test(int x,int y)
{
	std::cout << "test func:" << x*y << std::endl;
}

