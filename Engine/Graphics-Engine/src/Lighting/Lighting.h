#ifndef LIGHTING_H
#define LIGHTING_H

#include "../Tools/Includes.h"
#include "../Renderer/Renderer.h"

using namespace glm;

class GENGINE_API Lighting
{
	float ambientLightStrenth;
	vec3 ambientLightColor;

	bool directionalLightActive = false;
	vec3 directionalLightColor;
	vec3 directionalLightPosition;

	Renderer* renderer;
public:
	Lighting(Renderer* _renderer);
	Lighting(Renderer* _renderer, vec3 _ambientLightColor, float _ambientLightStrenth);
	~Lighting();
	void setAmbientLightStrenth(float value);
	void setAmbientLightColor(vec3 value);
	float getAmbientLightStrenth();
	vec3 getAmbientLightColor();
	void enableDirectionalLight(vec3 color, vec3 position);
	void disableDirectionalLight();
	void setDirectionalLightActive(bool value);
	bool getDirectionalLightActive();
	void setDirectionalLightPosition(vec3 value);
	vec3 getDirectionalLightPosition();
};

#endif // !LIGHTING_H