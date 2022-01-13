#pragma once
#include "Component.h"
#include "GameObject.h"
class TestComponent : public Component
{
public:
	COMPONENT_CLASS_CATEGOTY(Debug_Catagory);
	COMPONENT_CLASS_TYPE(Test_Type);
	TestComponent(GameObject* _mParentObject);
	~TestComponent();
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	void Test(int x, int y);
};

