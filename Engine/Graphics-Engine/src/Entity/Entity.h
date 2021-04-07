#ifndef ENTITY_H
#define ENTITY_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Transform/Transform.h"

using namespace glm;

struct GENGINE_API InternalData
{
	mat4 model;

	mat4 translate;
	mat4 rotationX;
	mat4 rotationY;
	mat4 rotationZ;
	mat4 scale;
};

const int VERTEX_BUFFER_SIZE = /*48*/ 396;

class GENGINE_API Entity
{
protected:
	float vertexBuffer[VERTEX_BUFFER_SIZE];

	InternalData internalData;
	Renderer* renderer;

	void updateModelMatrix();
public:
	Transform* transform;

	Entity(Renderer *_renderer);
	~Entity();
	Renderer* getRenderer();
	InternalData getInternalData();
	virtual void setPosition(float x, float y, float z);
	virtual void setScale(float x, float y, float z);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);
	void translate(float x, float y, float z);
	mat4 getModel();
	virtual void draw() = 0;
};

#endif // !ENTITY