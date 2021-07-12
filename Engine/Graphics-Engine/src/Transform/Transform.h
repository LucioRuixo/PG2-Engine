#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include "Tools/Includes.h"
//#include "Entity/Entity.h"

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

class Entity;

class GENGINE_API Transform
{
protected:
	int childCount;

	TRSMatrix trsMatrix;
	mat4 model;

	TransformData transformData;

	vector<Entity*> children;

	void updateModel();
public:
	Transform();
	Transform(vector<Entity*> _children);
	~Transform();

#pragma region Transformations
	virtual void setPosition(float x, float y, float z);
	vec3 getPosition();
	virtual void setRotation(float pitch, float yaw, float roll);
	vec3 getRotation();
	virtual void setScale(float x, float y, float z);
	vec3 getScale();
	mat4 getModel();
#pragma endregion

#pragma region Children
	vector<Entity*> getChildren();
	void addChild(Entity* child);
	void addChildren(vector<Entity*> newChildren);
	int getChildCount();
#pragma endregion
};

#endif // !TRANSFORM