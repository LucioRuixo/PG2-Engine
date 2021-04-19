#include "Transform.h"

Transform::Transform()
{
	transformData.position = vec3(0.0f, 0.0f, 0.0f);
	transformData.rotation = vec3(0.0f, 0.0f, 0.0f);
	transformData.scale = vec3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform() {}

void Transform::setPosition(float x, float y, float z)
{
	transformData.position.x = x;
	transformData.position.y = y;
	transformData.position.z = z;
}
vec3 Transform::getPosition() { return transformData.position; }

void Transform::setRotation(float x, float y, float z)
{
	transformData.rotation.x = x;
	transformData.rotation.y = y;
	transformData.rotation.z = z;
}
vec3 Transform::getRotation() { return transformData.rotation; }

void Transform::setScale(float x, float y, float z)
{
	transformData.scale.x = x;
	transformData.scale.y = y;
	transformData.scale.z = z;
}
vec3 Transform::getScale() { return transformData.scale; }