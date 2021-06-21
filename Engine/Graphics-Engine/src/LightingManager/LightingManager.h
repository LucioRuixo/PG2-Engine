#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "LightingManager/Light/Directional Light/DirectionalLight.h"
#include "LightingManager/Light/Point Light/PointLight.h"
#include "LightingManager/Light/Spotlight/Spotlight.h"

using namespace glm;

const int MAX_POINT_LIGHT_AMOUNT = 4;
const int MAX_SPOTLIGHT_AMOUNT = 4;

class GENGINE_API LightingManager
{
	vec3 ambient;

	DirectionalLight* directionalLight;
	PointLight* pointLights[MAX_POINT_LIGHT_AMOUNT];
	Spotlight* spotlights[MAX_SPOTLIGHT_AMOUNT];

	Renderer* renderer;
public:
	LightingManager(Renderer* _renderer);
	~LightingManager();
	void initializeShaderValues();

	void setAmbient(vec3 _ambient);
	vec3 getAmbient();

	void addDirectionalLight(vec3 direction);
	DirectionalLight* getDirectionalLight();
	void removeDirectionalLight();

	void addPointLight(int index, vec3 position);
	PointLight* getPointLight(int index);
	void removePointLight(int index);

	void addSpotlight(int index, vec3 position, vec3 direction);
	Spotlight* getSpotlight(int index);
	void removeSpotlight(int index);
};

#endif // !LIGHTING_MANAGER_H