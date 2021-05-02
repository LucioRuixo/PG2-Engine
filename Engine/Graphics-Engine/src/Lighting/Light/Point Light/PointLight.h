#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Tools/Includes.h"
#include "../Light.h"
#include "Entity/Cube/Light Cube/LightCube.h"

class GENGINE_API PointLight : public Light
{
	float constant;
	float linear;
	float quadratic;

	LightCube* lightCube;
public:
	PointLight(int _number, Renderer* _renderer);
	PointLight(int _number, Renderer* _renderer, vec3 _position);
	~PointLight();

	void setPosition(vec3 _position);
	vec3 getPosition();
	void setDirection(vec3 _direction);
	vec3 getDirection();

	void setLightingComponents(vec3 _diffuse, vec3 _specular);
	void setDiffuse(vec3 value);
	void setSpecular(vec3 value);

	void setTerms(float _constant, float _linear, float _quadratic);
	void setConstant(float _constant);
	float getConstant();
	void setLinear(float _linear);
	float getLinear();
	void setQuadratic(float _quadratic);
	float getQuadratic();

	void draw();
};

#endif // !POINT_LIGHT_H