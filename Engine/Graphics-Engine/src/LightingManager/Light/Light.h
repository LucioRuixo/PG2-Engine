#ifndef LIGHT_H
#define LIGHT_H

#include "Tools/Includes.h"
#include "Entity/Cube/Cube.h"

class GENGINE_API Light
{
protected:
	bool on;

	int index;
	char characterBuffer[64];

	vec3 position;
	vec3 direction;

	vec3 diffuse;
	vec3 specular;

	Renderer* renderer;
public:
	Light(Renderer* _renderer);
	~Light();

	virtual void setPosition(vec3 _position) = 0;
	virtual vec3 getPosition() = 0;
	virtual void setDirection(vec3 _direction) = 0;
	virtual vec3 getDirection() = 0;

	virtual void setLightingComponents(vec3 _diffuse, vec3 _specular) = 0;
	virtual void setDiffuse(vec3 value) = 0;
	vec3 getDiffuse();
	virtual void setSpecular(vec3 value) = 0;
	vec3 getSpecular();
	virtual void setOn(bool _on) = 0;
	bool getOn();

	virtual void draw() = 0;
};

#endif // !LIGHT_H