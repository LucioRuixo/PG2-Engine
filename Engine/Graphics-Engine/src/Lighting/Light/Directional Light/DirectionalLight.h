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

	void setPosition(vec3 _position) override;
	vec3 getPosition() override;
	void setDirection(vec3 _direction) override;
	vec3 getDirection() override;

	void setLightingComponents(vec3 _diffuse, vec3 _specular) override;
	void setDiffuse(vec3 value) override;
	void setSpecular(vec3 value) override;

	void draw() override;
};

#endif // !DIRECTIONAL_LIGHT_H