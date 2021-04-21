#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include "Tools/Includes.h"
#include "../Cube.h"

class GENGINE_API Light : public Cube
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
public:
	Light(Renderer* _renderer);
	Light(Renderer* _renderer, vec3 _ambient, vec3 _diffuse, vec3 _specular);
	~Light();
	void setAmbient(vec3 value);
	vec3 getAmbient();
	void setDiffuse(vec3 value);
	vec3 getDiffuse();
	void setSpecular(vec3 value);
	vec3 getSpecular();
	void draw();
};

#endif // !LIGHT_SOURCE_H