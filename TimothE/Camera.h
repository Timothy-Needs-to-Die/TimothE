#include "Transform.h"
class Camera {
	Camera(Transform transform) { _mTransform = transform; }
	~Camera() {}
	void Onstart();
	void OnUpdate();
	void OnEnd();
	Transform _mTransform;
};