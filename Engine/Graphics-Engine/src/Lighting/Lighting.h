#ifndef LIGHTING_H
#define LIGHTING_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Entity/Cube/Light/Light.h"

using namespace glm;

class GENGINE_API Lighting
{
	Light* lightSource;
	bool lightSourceActive = false;

	Renderer* renderer;
public:
	Lighting(Renderer* _renderer);
	~Lighting();

	void createLightSource();
	Light* getLightSource();
	void setLightSourceActive(bool value);
	bool getLightSourceActive();
	void setLightSourcePosition(vec3 value);
	vec3 getLightSourcePosition();
};

#endif // !LIGHTING_H