#include "Transform.h"

#include <GL/glew.h>
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"

class Camera {
public:
	//Vector2D _mFocusPosition;
	//float _mZoom;
	Transform _mTransform;

	Camera(Transform transform) { _mTransform = transform;  }
	~Camera() {}
	void Onstart();
	void OnUpdate();
	void OnEnd();
	 
};