#ifndef LIGHTING_H
#define LIGHTING_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Lighting/Light/Directional Light/DirectionalLight.h"
#include "Lighting/Light/Point Light/PointLight.h"
#include "Lighting/Light/Spotlight/Spotlight.h"

using namespace glm;

const int MAX_POINT_LIGHT_AMOUNT = 4;
const int MAX_SPOTLIGHT_AMOUNT = 4;

class GENGINE_API Lighting
{
	vec3 ambient;

	DirectionalLight* directionalLight;
	PointLight* pointLights[MAX_POINT_LIGHT_AMOUNT];
	Spotlight* spotlights[MAX_SPOTLIGHT_AMOUNT];

	Renderer* renderer;
public:
	Lighting(Renderer* _renderer);
	~Lighting();
	void initializeShaderValues();

	void setAmbient(vec3 _ambient);
	vec3 getAmbient();

	void addDirectionalLight(vec3 direction);
	DirectionalLight* getDirectionalLight();
	void removeDirectionalLight();

	void addPointLight(int number, vec3 position);
	PointLight* getPointLight(int number);
	void removePointLight(int number);

	void addSpotlight(int number, vec3 position, vec3 direction);
	Spotlight* getSpotlight(int number);
	void removeSpotlight(int number);
};

#endif // !LIGHTING_H