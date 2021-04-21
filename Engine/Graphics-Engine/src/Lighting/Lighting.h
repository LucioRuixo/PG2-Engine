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

#pragma region Light Source
	void enableLightSource(vec3 _position);
	void enableLightSource(vec3 _position, vec3 _ambient, vec3 _diffuse, vec3 _specular);
	Light* getLightSource();
	void disableLightSource();
	bool getLightSourceActive();
	void setLightSourcePosition(vec3 value);
	vec3 getLightSourcePosition();
#pragma endregion
};

#endif // !LIGHTING_H