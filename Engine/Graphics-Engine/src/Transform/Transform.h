#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Tools/Includes.h"

using namespace glm;

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