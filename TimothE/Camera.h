#include "Transform.h"

#include <GL/glew.h>
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"

class Camera {
public:
	Camera(Transform transform) { _mTransform = transform; }
	~Camera() {}
	void Onstart();
	void OnUpdate();
	void OnEnd();
	Transform _mTransform;
};