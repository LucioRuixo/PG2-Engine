#ifndef CAMERA_TRANSFORM_H
#define CAMERA_TRANSFORM_H

#include "Tools/Includes.h"
#include "../Transform.h"
#include "Renderer/Renderer.h"

using namespace std;
using namespace glm;

class GENGINE_API CameraTransform : public Transform
{
	mat4 view;

	Renderer* renderer;

	void updateView();
public:
	CameraTransform(Renderer* _renderer);
	~CameraTransform();

	void translate(float x, float y, float z) override;
	void setPosition(float x, float y, float z) override;
	void rotate(float pitch, float yaw, float roll) override;
	void setRotation(float pitch, float yaw, float roll) override;
	void setScale(float x, float y, float z) override;
};

#endif // !CAMERA_TRANSFORM