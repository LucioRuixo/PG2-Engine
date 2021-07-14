#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include "Tools/Includes.h"

using namespace std;
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
	vec3 forward;
	vec3 upVector;

	TRSMatrix trsMatrix;
	mat4 model;

	TransformData transformData;

	vector<Transform*> children;

public:
	void updateModel();
	Transform();
	Transform(vector<Transform*> _children);
	~Transform();

#pragma region Transformations
	void translate(float x, float y, float z);
	virtual void setPosition(float x, float y, float z);
	vec3 getPosition();

	void rotate(float pitch, float yaw, float roll);
	virtual void setRotation(float pitch, float yaw, float roll);
	vec3 getRotation();

	void scale(float x, float y, float z);
	virtual void setScale(float x, float y, float z);
	vec3 getScale();

	mat4 getModel();
	TRSMatrix getTRS();
#pragma endregion

#pragma region Children
	vector<Transform*> getChildren();
	void addChild(Transform* child);
	void addChildren(vector<Transform*> newChildren);
#pragma endregion
};

#endif // !TRANSFORM