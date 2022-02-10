#ifndef FRUSTUM_PLANE_H
#define FRUSTUM_PLANE_H

#include "Tools/Includes.h"
#include "Entity/Plane/Plane.h"

class GENGINE_API FrustumPlane : public Plane
{
public:
	FrustumPlane();
	FrustumPlane(vec3 _color);
	FrustumPlane(Material _material);
	FrustumPlane(vec3 _color, Material _material);
};

#endif // !FRUSTUM_PLANE_H