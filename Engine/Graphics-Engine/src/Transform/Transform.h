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

struct GENGINE_API LocalModelMatrix
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

	LocalModelMatrix localModel;
	mat4 globalModel;

	TransformData transformData;

	Transform* parent = NULL;
	vector<Transform*> children;

public:
	void updateLocalModel();
	void updateGlobalModel();
	void updateGlobalModel(mat4 other);

	Transform();
	Transform(vector<Transform*> _children);
	~Transform();

	//TODO: como las transformaciones por ahora son locales, agregar también métodos globales
#pragma region Transformations
	virtual void translate(float x, float y, float z);
	virtual void setPosition(float x, float y, float z);
	vec3 getPosition();

	virtual void rotate(float pitch, float yaw, float roll);
	virtual void setRotation(float pitch, float yaw, float roll);
	vec3 getRotation();

	virtual void scale(float x, float y, float z);
	virtual void setScale(float x, float y, float z);
	vec3 getScale();

	vec3 getRight();
	vec3 getUp();
	vec3 getForward();

	mat4 getLocalModel();
	mat4 getGlobalModel();
	//ModelMatrix getTRS();
#pragma endregion

#pragma region Children
	vector<Transform*> getChildren();
	void addChild(Transform* child);
	void removeChild(Transform* child);
#pragma endregion

	//TODO: comprobar que las transformaciones sigan bien después de modificar el padre
#pragma region Parent
	void setParent(Transform* _parent);
	Transform* getParent();
#pragma endregion
};

#endif // !TRANSFORM