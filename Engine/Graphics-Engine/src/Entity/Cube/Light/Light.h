#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include "Tools/Includes.h"
#include "../Cube.h"

enum LightType
{
	Directional,
	Point,
	Spot
};

class GENGINE_API Light : public Cube
{
	LightType type;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
public:
	Light(Renderer* _renderer, LightType _type);
	~Light();

	void setPosition(float x, float y, float z);
	void translate(float x, float y, float z);

	void setType(LightType value);
	LightType getType();

	void setDirection(vec3 value);
	vec3 getDirection();

	void setLightingComponents(vec3 _ambient, vec3 _diffuse, vec3 _specular);
	void setAmbient(vec3 value);
	vec3 getAmbient();
	void setDiffuse(vec3 value);
	vec3 getDiffuse();
	void setSpecular(vec3 value);
	vec3 getSpecular();
	void draw();
};

#endif // !LIGHT_SOURCE_H