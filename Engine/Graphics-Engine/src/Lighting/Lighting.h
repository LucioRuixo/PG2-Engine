#ifndef LIGHTING_H
#define LIGHTING_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"

using namespace glm;

class GENGINE_API Lighting
{
	float ambientLightStrenth;
	vec3 ambientLightColor;

	bool lightSourceActive = false;
	vec3 lightSourceColor;
	vec3 lightSourcePosition;

	Renderer* renderer;
public:
	Lighting(Renderer* _renderer);
	Lighting(Renderer* _renderer, vec3 _ambientLightColor, float _ambientLightStrenth);
	~Lighting();
	void setAmbientLightStrenth(float value);
	void setAmbientLightColor(vec3 value);
	float getAmbientLightStrenth();
	vec3 getAmbientLightColor();
	void enableLightSource(vec3 color, vec3 position);
	void disableLightSource();
	void setLightSourceActive(bool value);
	bool getLightSourceActive();
	void setLightSourcePosition(vec3 value);
	vec3 getLightSourcePosition();
};

#endif // !LIGHTING_H