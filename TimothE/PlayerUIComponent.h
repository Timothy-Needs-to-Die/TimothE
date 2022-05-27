#pragma once
#include "Component.h"
#include <vector>

class PlayerUIComponent : public Component
{
public:
	COMPONENT_STATIC_TYPE(PlayerUI_Type);

	PlayerUIComponent(GameObject* parent);

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;

	void SetBuildModeUIActive(bool val);
	void SetFarmModeUIActive(bool val);

private:
	std::vector<class TextObject*> _pBuildModeUI;
	std::vector<class TextObject*> _pFarmModeUI;
};
