#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <string>
#include "Tools/Includes.h"
#include "Entity/Cube/Light Cube/LightCube.h"
#include "../Light.h"

class GENGINE_API Spotlight : public Light
{
	float innerCutOff;
	float outerCutOff;

	LightCube* lightCube;
public:
	Spotlight(int _number, Renderer* _renderer);
	Spotlight(int _number, Renderer* _renderer, vec3 _position, vec3 _direction);
	~Spotlight();

	void setPosition(vec3 _position);
	vec3 getPosition();
	void setDirection(vec3 _direction);
	vec3 getDirection();

	void setLightingComponents(vec3 _diffuse, vec3 _specular);
	void setDiffuse(vec3 value);
	void setSpecular(vec3 value);

	void setInnerCutOff(float _innerCutOff);
	float getInnerCutOff();
	void setOuterCutOff(float _outerCutOff);
	float getOuterCutOff();

	void draw();
};

#endif // !SPOT_LIGHT_H