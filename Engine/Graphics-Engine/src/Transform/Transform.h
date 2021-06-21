#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Tools/Includes.h"

using namespace glm;

struct GENGINE_API TransformData
{
	vec3 position;
	vec3 rotation;
	vec3 scale;
};

struct GENGINE_API ModelMatrixData
{
	mat4 model;

	mat4 translation;
	mat4 rotationX;
	mat4 rotationY;
	mat4 rotationZ;
	mat4 scale;
};

class GENGINE_API Transform
{
	TransformData transformData;
public:
	Transform();
	~Transform();

	void setPosition(float x, float y, float z);
	vec3 getPosition();
	void setRotation(float x, float y, float z);
	vec3 getRotation();
	void setScale(float x, float y, float z);
	vec3 getScale();
};

#endif // !TRANSFORM