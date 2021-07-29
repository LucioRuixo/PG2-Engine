#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
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
	vec3 right;
	vec3 up;
	vec3 forward;

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
	virtual void translate(float x, float y, float z);
	virtual void setPosition(float x, float y, float z);
	vec3 getPosition();

	virtual void rotate(float pitch, float yaw, float roll);
	virtual void setRotation(float pitch, float yaw, float roll);
	vec3 getRotation();
	void rotateAroundPivot(float pitch, float yaw, float roll, Transform* pivot);

	virtual void scale(float x, float y, float z);
	virtual void setScale(float x, float y, float z);
	vec3 getScale();

	vec3 getRight();
	vec3 getUp();
	vec3 getForward();

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