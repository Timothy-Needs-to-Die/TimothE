#pragma once
#include "Component.h"


class TestComponent : public Component
{
public:
	TestComponent(GameObject* pParent) : Component(pParent) {
		SetType(Component::Types::Test_Type);
		SetCategory(Component::Categories::Debug_Category);
		OnStart();
	}

	COMPONENT_STATIC_TYPE(Test_Type)

	~TestComponent();
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	void Test(int x, int y);

	

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override {
		Component::SaveState(stream);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		Component::LoadState(stream);

		return true;
	}
	// Inherited via Component
	virtual void DrawEditorUI() override;
};

