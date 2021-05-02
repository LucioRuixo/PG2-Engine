#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Tools/Includes.h"
#include "../Light.h"

class GENGINE_API DirectionalLight : public Light
{
public:
	DirectionalLight(Renderer* _renderer);
	DirectionalLight(Renderer* _renderer, vec3 _direction);
	~DirectionalLight();

	void setPosition(vec3 _position);
	vec3 getPosition();
	void setDirection(vec3 _direction);
	vec3 getDirection();

	void setLightingComponents(vec3 _diffuse, vec3 _specular);
	void setDiffuse(vec3 value);
	void setSpecular(vec3 value);

	void draw();
};

#endif // !DIRECTIONAL_LIGHT_H