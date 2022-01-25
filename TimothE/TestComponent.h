#pragma once
#include "Component.h"


class TestComponent : public Component
{
public:
	TestComponent(GameObject* pParent);

	COMPONENT_STATIC_TYPE(Test_Type)

	~TestComponent();
	void OnStart() override;
	void OnUpdate(float deltaTime) override;
	void OnEnd() override;
	virtual void DrawEditorUI() override;

	void Test(int x, int y);
	

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override;
	virtual bool LoadState(IStream& stream) override;
};

