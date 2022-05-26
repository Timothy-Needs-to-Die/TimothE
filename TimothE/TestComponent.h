#pragma once
#include "Component.h"


class TestComponent : public Component
{
public:
	TestComponent(GameObject* pParent);

	COMPONENT_STATIC_TYPE(Test_Type)

	~TestComponent();
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	virtual void DrawEditorUI() override;

	void Test(int x, int y);
	
};

