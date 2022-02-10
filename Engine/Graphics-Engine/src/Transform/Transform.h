#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Tools/Includes.h"

using namespace std;
using namespace glm;

struct GENGINE_API TransformData
{
	vec3 position;
	vec3 rotation;
	vec3 scale;
};

struct GENGINE_API ModelMatrix
{
	mat4 model;

	mat4 translation;
	mat4 rotationX;
	mat4 rotationY;
	mat4 rotationZ;
	mat4 rotation;
	mat4 scale;
};

class GENGINE_API Transform
{
protected:
	vec3 right;
	vec3 up;
	vec3 forward;

	ModelMatrix localModel;
	mat4 globalModel;

	TransformData localData;
	TransformData globalData;

	Transform* parent = NULL;
	vector<Transform*> children;

	void initialize();
	float positiveDegrees(float degrees);
	float eulerAngles(float radians);
	vec3 eulerAngles(vec3 radians);
	void decompose(mat4 matrix); // Debug
	void decompose(mat4 matrix, vec3& translation, vec3& eulerRotation, vec3& scale);
	void decompose(mat4 matrix, vec3& translation, quat& quatRotation, vec3& scale);

	virtual void processRotation(float pitch, float yaw, float roll);

protected:
	bool transformedSinceCBUpdate = true;

public:
	void updateDirectionVectors(float pitch, float yaw, float roll);
	void updateChildrenDirectionVectors(float pitch, float yaw, float roll, vec3 xAxis, vec3 yAxis, vec3 zAxis);
	virtual void updateLocalModel();
	virtual void updateGlobalModel();
	virtual void updateGlobalModel(mat4 other);

	Transform();
	Transform(vector<Transform*> _children);
	~Transform();

#pragma region CollisionBox
	void setTransformedSinceCBUpdate(bool _transformedSinceCBUpdate);
	bool getTransformedSinceCBUpdate();
#pragma endregion

#pragma region Transformations
	virtual void translate(float x, float y, float z);
	virtual void translate(vec3 translation);
	virtual void setPosition(float x, float y, float z);
	virtual void setPosition(vec3 position);
	virtual vec3 getPosition();
	vec3 getGlobalPosition();

	virtual void rotate(float pitch, float yaw, float roll);
	virtual void setRotation(float pitch, float yaw, float roll);
	virtual void setRotation(vec3 rotation);
	vec3 getRotation();
	vec3 getGlobalRotation();

	virtual void scale(float x, float y, float z);
	virtual void setScale(float x, float y, float z);
	virtual void setScale(vec3 scale);
	vec3 getScale();
	vec3 getGlobalScale();

	vec3 getRight();
	vec3 getUp();
	vec3 getForward();
	
	mat4 getLocalModel();
	mat4 getGlobalModel();
#pragma endregion

#pragma region Children
	vector<Transform*> getChildren();
	void addChild(Transform* child);
	void removeChild(Transform* child);
#pragma endregion

#pragma region Parent
	void setParent(Transform* _parent);
	Transform* getParent();
#pragma endregion
};

#endif // !TRANSFORM