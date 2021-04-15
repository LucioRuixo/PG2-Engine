#ifndef CAMERA_H
#define CAMERA_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Transform/Transform.h"

using namespace glm;

class GENGINE_API Camera
{
	//ModelMatrixData matrixData;
	vec3 direction;
	vec3 right;
	vec3 up;
	mat4 view;

	Renderer* renderer;

	void updateViewMatrix();
public:
	Transform* transform;

	Camera(Renderer* renderer);
	~Camera();
	void setPosition(float x, float y, float z);
	void translate(float x, float y, float z);
	void setRotation(float pitch, float yaw, float roll);
	void rotate(float pitch, float yaw, float roll);
};

#endif // !CAMERA_H