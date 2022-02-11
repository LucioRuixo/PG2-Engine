#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Tools/Includes.h"
#include "Entity/Plane/FrustumPlane/FrustumPlane.h"
#include "Transform/CameraTransform/CameraTransform.h"

enum FrustumPlanes
{
	Near,
	Far,
	Up,
	Down,
	Right,
	Left,
	Length
};

class GENGINE_API Frustum : public Entity
{
	FrustumData data;
	vector<FrustumPlane*> planes;

public:
	Frustum(FrustumData _data, CameraTransform* cameraTransform);
	~Frustum();

	FrustumData getFrustumData();
	FrustumPlane* getPlane(FrustumPlanes plane);

	bool isInside(vec3 point);
	bool isInside(Entity* entity);

#pragma Collision Box
	vector<vec3> getCollisionVertices() override;
#pragma endregion

	void draw();
};

#endif // !FRUSTUM_H