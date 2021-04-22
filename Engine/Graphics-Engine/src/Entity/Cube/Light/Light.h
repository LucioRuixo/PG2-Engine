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

	float constant;
	float linear;
	float quadratic;

	float innerCutOff;
	float outerCutOff;
public:
	Light(Renderer* _renderer, LightType _type);
	~Light();

	void setPosition(float x, float y, float z);
	void translate(float x, float y, float z);
	void setDirection(vec3 _direction);
	vec3 getDirection();

	void setType(LightType _type);
	LightType getType();

#pragma region Lighting Components
	void setLightingComponents(vec3 _ambient, vec3 _diffuse, vec3 _specular);
	void setAmbient(vec3 value);
	vec3 getAmbient();
	void setDiffuse(vec3 value);
	vec3 getDiffuse();
	void setSpecular(vec3 value);
	vec3 getSpecular();
#pragma endregion

#pragma region Point Light
	void setPointLightTerms(float _constant, float _linear, float _quadratic);
	void setConstant(float _constant);
	float getConstant();
	void setLinear(float _linear);
	float getLinear();
	void setQuadratic(float _quadratic);
	float getQuadratic();
#pragma endregion

#pragma region Spot Light
	void setInnerCutOff(float _innerCutOff);
	float getInnerCutOff();
	void setOuterCutOff(float _outerCutOff);
	float getOuterCutOff();
#pragma endregion

	void draw();
};

#endif // !LIGHT_SOURCE_H