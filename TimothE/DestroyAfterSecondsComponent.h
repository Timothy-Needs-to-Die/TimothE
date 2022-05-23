#include "Component.h"

class DestroyAfterSecondsComponent : public Component {
public:
	COMPONENT_STATIC_TYPE(DestroyAfterSeconds_Type);

	DestroyAfterSecondsComponent(GameObject* owner, float duration = 5.0f);

	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;


private:
	float _duration; 
	float _timer;

};