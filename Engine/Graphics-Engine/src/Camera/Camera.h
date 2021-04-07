#ifndef CAMERA_H
#define CAMERA_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Transform/Transform.h"

using namespace glm;

class GENGINE_API Camera
{
	Renderer* renderer;

	void setTransformPosition(float x, float y, float z);
public:
	Transform* transform;

	Camera(Renderer* renderer);
	~Camera();
	void setPosition(float x, float y, float z);
	void setPosition(vec3 value);
	void translate(float x, float y, float z);
	void translate(vec3 translation);
};

#endif // !CAMERA_H