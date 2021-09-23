#include "ModelTransform.h"

ModelTransform::ModelTransform(ModelNode* _rootNode) : Transform()
{
	rootNode = _rootNode;
}

ModelTransform::~ModelTransform() {}

void ModelTransform::translate(float x, float y, float z)
{
	Transform::translate(x, y, z);

	rootNode->updateModels(globalModel);
}

void ModelTransform::setPosition(float x, float y, float z)
{
	float translationX = x - transformData.position.x;
	float translationY = y - transformData.position.y;
	float translationZ = z - transformData.position.z;

	translate(translationX, translationY, translationZ);
}

void ModelTransform::rotate(float pitch, float yaw, float roll)
{
	Transform::rotate(pitch, yaw, roll);

	rootNode->updateModels(globalModel);
}

void ModelTransform::setRotation(float pitch, float yaw, float roll)
{
	float rotationX = pitch - transformData.rotation.x;
	float rotationY = yaw - transformData.rotation.y;
	float rotationZ = roll - transformData.rotation.z;

	rotate(rotationX, rotationY, rotationZ);
}

void ModelTransform::scale(float x, float y, float z)
{
	Transform::scale(x, y, z);

	rootNode->updateModels(globalModel);
}

void ModelTransform::setScale(float x, float y, float z)
{
	float scaleX = x - transformData.scale.x;
	float scaleY = y - transformData.scale.y;
	float scaleZ = z - transformData.scale.z;

	scale(scaleX, scaleY, scaleZ);
}