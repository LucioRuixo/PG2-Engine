#include "Transform.h"

Transform::Transform()
{
	transformData.position = vec3(0.0f, 0.0f, 0.0f);
	transformData.rotation = vec3(0.0f, 0.0f, 0.0f);
	transformData.scale = vec3(1.0f, 1.0f, 1.0f);

	model = mat4(1.0f);

	trsMatrix.translation = mat4(1.0f);
	trsMatrix.rotationX = mat4(1.0f);
	trsMatrix.rotationY = mat4(1.0f);
	trsMatrix.rotationZ = mat4(1.0f);
	trsMatrix.scale = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	setScale(1.0f, 1.0f, 1.0f);
}

Transform::~Transform() {}

void Transform::updateModel()
{
	model = trsMatrix.translation *
		trsMatrix.rotationX * trsMatrix.rotationY * trsMatrix.rotationZ *
		trsMatrix.scale;
}

void Transform::setPosition(float x, float y, float z)
{
	transformData.position.x = x;
	transformData.position.y = y;
	transformData.position.z = z;

	trsMatrix.translation = translate(mat4(1.0f), transformData.position);
	updateModel();
}
vec3 Transform::getPosition() { return transformData.position; }

void Transform::setRotation(float pitch, float yaw, float roll)
{
	transformData.rotation.x = pitch;
	transformData.rotation.y = yaw;
	transformData.rotation.z = roll;

	vec3 xAxis = vec3(1.0f, 0.0f, 0.0f);
	vec3 yAxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 zAxis = vec3(0.0f, 0.0f, 1.0f);

	trsMatrix.rotationX = rotate(mat4(1.0f), radians(pitch), xAxis);
	trsMatrix.rotationY = rotate(mat4(1.0f), radians(yaw), yAxis);
	trsMatrix.rotationZ = rotate(mat4(1.0f), radians(roll), zAxis);

	updateModel();
}
vec3 Transform::getRotation() { return transformData.rotation; }

void Transform::setScale(float x, float y, float z)
{
	transformData.scale.x = x;
	transformData.scale.y = y;
	transformData.scale.z = z;

	trsMatrix.scale = scale(mat4(1.0f), transformData.scale);
	updateModel();
}
vec3 Transform::getScale() { return transformData.scale; }

mat4 Transform::getModel() { return model; }
