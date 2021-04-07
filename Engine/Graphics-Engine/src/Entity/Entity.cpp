#include "Entity.h"

Entity::Entity(Renderer *_renderer)
{
	renderer = _renderer;

	internalData.model = mat4(1.0f);
	internalData.rotationX = mat4(1.0f);
	internalData.rotationY = mat4(1.0f);
	internalData.rotationZ = mat4(1.0f);
	internalData.scale = mat4(1.0f);
	internalData.translate = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotationX(0.0f);
	setRotationY(0.0f);
	setRotationZ(0.0f);
	setScale(1.0f, 1.0f, 1.0f);
}

Entity::~Entity() {}

void Entity::updateModelMatrix()
{
	internalData.model = internalData.translate *
						 internalData.rotationX * internalData.rotationY * internalData.rotationZ *
						 internalData.scale;
}

Renderer* Entity::getRenderer() { return renderer; }

InternalData Entity::getInternalData() { return internalData; }

void Entity::setPosition(float x, float y, float z)
{
	transform.position = vec3(x, y, z);

	internalData.translate = glm::translate(mat4(1.0f), transform.position);
	updateModelMatrix();
}

void Entity::setScale(float x, float y, float z)
{
	transform.scale = vec3(x, y, z);

	internalData.scale = scale(mat4(1.0f), transform.scale);
	updateModelMatrix();
}

void Entity::setRotationX(float x)
{
	transform.rotation.x = x;
	vec3 axis = vec3(1.0f, 0.0f, 0.0f);

	internalData.rotationX = rotate(mat4(1.0f), x, axis);
	updateModelMatrix();
}

void Entity::setRotationY(float y)
{
	transform.rotation.y = y;
	vec3 axis = vec3(0.0f, 1.0f, 0.0f);

	internalData.rotationY = rotate(mat4(1.0f), y, axis);
	updateModelMatrix();
}

void Entity::setRotationZ(float z)
{
	transform.rotation.z = z;
	vec3 axis = vec3(0.0f, 0.0f, 1.0f);

	internalData.rotationZ = rotate(mat4(1.0f), z, axis);
	updateModelMatrix();
}

void Entity::translate(float x, float y, float z)
{
	transform.position = vec3(x, y, z);

	internalData.translate = glm::translate(mat4(1.0f), transform.position);
	updateModelMatrix();
}

mat4 Entity::getModel() { return internalData.model; }