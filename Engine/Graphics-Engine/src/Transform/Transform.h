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

struct GENGINE_API TRSMatrix
{
	mat4 translation;
	mat4 rotationX;
	mat4 rotationY;
	mat4 rotationZ;
	mat4 scale;
};

class GENGINE_API Transform
{
protected:
	TRSMatrix trsMatrix;
	mat4 model;

	TransformData transformData;

	void updateModel();
public:
	Transform();
	~Transform();

	virtual void setPosition(float x, float y, float z);
	vec3 getPosition();
	virtual void setRotation(float pitch, float yaw, float roll);
	vec3 getRotation();
	virtual void setScale(float x, float y, float z);
	vec3 getScale();
	mat4 getModel();
};

#endif // !TRANSFORM