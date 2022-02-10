#include "FrustumPlane.h"

FrustumPlane::FrustumPlane() : Plane(false) {}

FrustumPlane::FrustumPlane(vec3 _color) : Plane(_color, false) {}

FrustumPlane::FrustumPlane(Material _material) : Plane(_material, false) {}

FrustumPlane::FrustumPlane(vec3 _color, Material _material) : Plane(_color, _material, false) {}