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

	void setPosition(vec3 _position) override;
	vec3 getPosition() override;
	void setDirection(vec3 _direction) override;
	vec3 getDirection() override;

	void setLightingComponents(vec3 _diffuse, vec3 _specular) override;
	void setDiffuse(vec3 value) override;
	void setSpecular(vec3 value) override;

	void setInnerCutOff(float _innerCutOff);
	float getInnerCutOff();
	void setOuterCutOff(float _outerCutOff);
	float getOuterCutOff();
	void setOn(bool _on) override;

	void draw() override;
};

#endif // !SPOT_LIGHT_H