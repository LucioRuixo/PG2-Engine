#ifndef ENTITY_H
#define ENTITY_H

#include "Includes.h"
#include "Renderer.h"

struct GENGINE_API Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct GENGINE_API InternalData {
	glm::mat4 model;
	glm::mat4 translate;
	glm::mat4 rotateX;
	glm::mat4 rotateY;
	glm::mat4 rotateZ;
	glm::mat4 scale;
};

const int QUAD_VERTEX_BUFFER_SIZE = 48;

class GENGINE_API Entity {
protected:
	float vertexBuffer[QUAD_VERTEX_BUFFER_SIZE];
	Renderer* renderer;
	InternalData internalData;
	void UpdateMatrixModel();
public:
	Entity(Renderer *_renderer);
	Transform transform;
	Renderer* GetRenderer();
	InternalData GetInternalData();
	virtual void SetPosition(float x, float y, float z);
	virtual void SetScale(float x, float y, float z);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void Translate(float x, float y, float z);
	glm::mat4 getModel();
};

#endif // !ENTITY