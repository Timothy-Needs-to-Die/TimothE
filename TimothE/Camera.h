#include "Transform.h"

#include <GL/glew.h>
#include <glm.hpp>
class Camera {
public:
	Camera(Transform transform) { _mTransform = transform; }
	~Camera() {}
	void Onstart();
	void OnUpdate();
	void OnEnd();
	Transform _mTransform;
	glm::vec3 _mEye = {0,0,0};
	glm::vec3 _mCenter = { 0,0,0 };
	glm::vec3 _mUp = { 0,0,0 };
};