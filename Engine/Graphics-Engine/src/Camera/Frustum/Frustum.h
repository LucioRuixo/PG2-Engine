#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Tools/Includes.h"
#include "Entity/Plane/Plane.h"
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
	vector<Plane*> planes;

public:
	Frustum(FrustumData _data, CameraTransform* cameraTransform);
	~Frustum();

	FrustumData getFrustumData();
	Plane* getPlane(FrustumPlanes plane);

	bool isInside(vec3 point);

	void draw();
};

#endif // !FRUSTUM_H