#ifndef CAMERA_H
#define CAMERA_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Transform/CameraTransform/CameraTransform.h"

using namespace glm;

class GENGINE_API Camera
{
	Renderer* renderer;
	CameraTransform* transform;
public:
	Camera(Renderer* _renderer);
	~Camera();

	CameraTransform* getTransform();
};

#endif // !CAMERA_H