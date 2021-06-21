#include "Light.h"

Light::Light(Renderer* _renderer)
{
	renderer = _renderer;
}

Light::~Light() {}

vec3 Light::getDiffuse() { return diffuse; }

vec3 Light::getSpecular() { return specular; }

bool Light::getOn() { return on; }