#ifndef LIGHTING_H
#define LIGHTING_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Entity/Entity2D/Plane/Sprite/Sprite.h"

using namespace glm;

class GENGINE_API Lighting
{
	float ambientLightStrength = 0.1f;
	vec3 ambientLightColor = vec3(1.0f, 1.0f, 1.0f);

	bool lightSourceActive = false;
	vec3 lightSourceColor;
	vec3 lightSourcePosition;
	const char* lightSourceIconPath;
	Sprite* lightSourceIcon;

	float specularStrength = 0.5f;

	Renderer* renderer;
public:
	Lighting(Renderer* _renderer);
	Lighting(Renderer* _renderer, vec3 _ambientLightColor, float _ambientLightStrength);
	~Lighting();

	//Ambient light
	void setAmbientLightStrength(float value);
	void setAmbientLightColor(vec3 value);
	float getAmbientLightStrength();
	vec3 getAmbientLightColor();

	//Light source
	void enableLightSource(vec3 color, vec3 position);
	void disableLightSource();
	void setLightSourceActive(bool value);
	bool getLightSourceActive();
	void setLightSourcePosition(vec3 value);
	vec3 getLightSourcePosition();
	Sprite* getLightSourceIcon();

	//Specular
	void setSpecularStrength(float value);
	float getSpecularStrength();
};

#endif // !LIGHTING_H