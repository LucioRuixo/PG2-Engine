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

	void setPosition(vec3 _position) override;
	vec3 getPosition() override;
	void setDirection(vec3 _direction) override;
	vec3 getDirection() override;

	void setLightingComponents(vec3 _diffuse, vec3 _specular) override;
	void setDiffuse(vec3 value) override;
	void setSpecular(vec3 value) override;

	void setTerms(float _constant, float _linear, float _quadratic);
	void setConstant(float _constant);
	float getConstant();
	void setLinear(float _linear);
	float getLinear();
	void setQuadratic(float _quadratic);
	float getQuadratic();

	void draw() override;
};

#endif // !POINT_LIGHT_H