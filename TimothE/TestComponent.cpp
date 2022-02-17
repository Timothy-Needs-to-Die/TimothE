#include "TestComponent.h"

TestComponent::TestComponent(GameObject* pParent) : Component(pParent)
{
	SetType(Component::Types::Test_Type);
	SetCategory(Component::Categories::Debug_Category);
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
void TestComponent::OnUpdate(float deltaTime)
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

// Inherited via ISerializable

inline bool TestComponent::SaveState(IStream& stream) const {
	Component::SaveState(stream);

	return true;
}

inline bool TestComponent::LoadState(IStream& stream) {
	Component::LoadState(stream);

	return true;
}

void TestComponent::DrawEditorUI()
{

}



