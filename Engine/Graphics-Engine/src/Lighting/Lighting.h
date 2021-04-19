#ifndef LIGHTING_H
#define LIGHTING_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Entity/Plane/Sprite/Sprite.h"

using namespace glm;

class GENGINE_API Sprite;

struct Light
{
	vec3 position = vec3(0.0f, 3.0f, 0.0f);

	vec3 ambient = vec3(0.1f);
	vec3 diffuse = vec3(1.0f);
	vec3 specular = vec3(1.0f);
};

class GENGINE_API Lighting
{
	Light lightSource;
	bool lightSourceActive = false;
	const char* lightSourceIconPath;
	Sprite* lightSourceIcon;

	Renderer* renderer;
public:
	Lighting(Renderer* _renderer);
	Lighting(Renderer* _renderer, Light _lightSource);
	~Lighting();

#pragma region Light Source
	void enableLightSource(Light _lightSource);
	void disableLightSource();
	void setLightSourceActive(bool value);
	bool getLightSourceActive();
	void setLightSourcePosition(vec3 value);
	vec3 getLightSourcePosition();
	Sprite* getLightSourceIcon();
#pragma endregion
};

#endif // !LIGHTING_H