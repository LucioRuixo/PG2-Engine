#ifndef CAMERA_TRANSFORM_H
#define CAMERA_TRANSFORM_H

#include "Tools/Includes.h"
#include "../Transform.h"
#include "Camera/Frustum/Frustum.h"
#include "Renderer/Renderer.h"

using namespace std;
using namespace glm;

class GENGINE_API CameraTransform : public Transform
{
	bool frustumAttached = true;
	mat4 view;
	Renderer* renderer;

	bool frustumCulling = false;
	Frustum* frustum;

	void updateView(mat4 _view);

public:
	CameraTransform(Renderer* _renderer);
	~CameraTransform();

	void translate(float x, float y, float z) override;
	void setPosition(float x, float y, float z) override;
	vec3 getPosition() override;

	void rotate(float pitch, float yaw, float roll) override;
	void setRotation(float pitch, float yaw, float roll) override;

	void setScale(float x, float y, float z) override;

#pragma region Frustum Culling
	Frustum* getFrustum();

	void enableFrustumCulling(FrustumData frustumData);
	void disableFrustumCulling();
	bool getFrustumCulling();

	void toggleFrustumAttachment();
	bool getFrustumAttached();
#pragma endregion
};

#endif // !CAMERA_TRANSFORM