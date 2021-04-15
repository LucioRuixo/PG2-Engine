#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Tools/Includes.h"

using namespace glm;

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
public:
	vec3 position;
	vec3 rotation;
	vec3 scale;

	Transform();
	~Transform();
};

#endif // !TRANSFORM