#include "Entity.h"

Entity::Entity(Renderer *_renderer)
{
	renderer = _renderer;
	transform = new Transform();

	matrixData.mainMatrix = mat4(1.0f);
	matrixData.rotationX = mat4(1.0f);
	matrixData.rotationY = mat4(1.0f);
	matrixData.rotationZ = mat4(1.0f);
	matrixData.scale = mat4(1.0f);
	matrixData.translation = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotationX(0.0f);
	setRotationY(0.0f);
	setRotationZ(0.0f);
	setScale(1.0f, 1.0f, 1.0f);
}

Entity::~Entity() { if (transform) delete transform; }

void Entity::updateModelMatrix()
{
	matrixData.mainMatrix = matrixData.translation *
							matrixData.rotationX * matrixData.rotationY * matrixData.rotationZ *
							matrixData.scale;
}

Renderer* Entity::getRenderer() { return renderer; }

MatrixData Entity::getInternalData() { return matrixData; }

void Entity::setPosition(float x, float y, float z)
{
	transform->position = vec3(x, y, z);

	matrixData.translation = glm::translate(mat4(1.0f), transform->position);
	updateModelMatrix();
}

void Entity::setScale(float x, float y, float z)
{
	transform->scale = vec3(x, y, z);

	matrixData.scale = scale(mat4(1.0f), transform->scale);
	updateModelMatrix();
}

void Entity::setRotationX(float x)
{
	transform->rotation.x = x;
	vec3 axis = vec3(1.0f, 0.0f, 0.0f);

	matrixData.rotationX = rotate(mat4(1.0f), x, axis);
	updateModelMatrix();
}

void Entity::setRotationY(float y)
{
	transform->rotation.y = y;
	vec3 axis = vec3(0.0f, 1.0f, 0.0f);

	matrixData.rotationY = rotate(mat4(1.0f), y, axis);
	updateModelMatrix();
}

void Entity::setRotationZ(float z)
{
	transform->rotation.z = z;
	vec3 axis = vec3(0.0f, 0.0f, 1.0f);

	matrixData.rotationZ = rotate(mat4(1.0f), z, axis);
	updateModelMatrix();
}

void Entity::translate(float x, float y, float z)
{
	transform->position = vec3(x, y, z);

	matrixData.translation = glm::translate(mat4(1.0f), transform->position);
	updateModelMatrix();
}

mat4 Entity::getModel() { return matrixData.mainMatrix; }