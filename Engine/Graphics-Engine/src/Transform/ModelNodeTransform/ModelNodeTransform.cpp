#include "ModelNodeTransform.h"

ModelNodeTransform::ModelNodeTransform() : Transform() {}

ModelNodeTransform::ModelNodeTransform(Plane* _bspPlane) : Transform() { setBSPPlane(_bspPlane); }

ModelNodeTransform::~ModelNodeTransform() {}

void ModelNodeTransform::initializeValues(vec3 _position, vec3 _rotation, vec3 _scale)
{
	transformData.position = _position;
	transformData.rotation = _rotation;
	transformData.scale = _scale;
}

void ModelNodeTransform::updateGlobalModel(mat4 other)
{
	globalModel = other * localModel.model;

	if (bspPlane) bspPlane->updateModels(other);
}

void ModelNodeTransform::translate(float x, float y, float z)
{
	Transform::translate(x, y, z);

	if (bspPlane) bspPlane->getTransform()->translate(x, y, z);
}

void ModelNodeTransform::setPosition(float x, float y, float z)
{
	float translationX = x - transformData.position.x;
	float translationY = y - transformData.position.y;
	float translationZ = z - transformData.position.z;

	translate(translationX, translationY, translationZ);
}

void ModelNodeTransform::rotate(float pitch, float yaw, float roll)
{
	Transform::rotate(pitch, yaw, roll);

	if (bspPlane) bspPlane->getTransform()->rotate(pitch, yaw, roll);
}

void ModelNodeTransform::setRotation(float pitch, float yaw, float roll)
{
	float rotationX = pitch - transformData.rotation.x;
	float rotationY = yaw - transformData.rotation.y;
	float rotationZ = roll - transformData.rotation.z;

	rotate(rotationX, rotationY, rotationZ);
}

void ModelNodeTransform::scale(float x, float y, float z)
{
	Transform::scale(x, y, z);

	if (bspPlane) bspPlane->getTransform()->scale(x, y, z);
}

void ModelNodeTransform::setScale(float x, float y, float z)
{
	float scaleX = x - transformData.scale.x;
	float scaleY = y - transformData.scale.y;
	float scaleZ = z - transformData.scale.z;

	scale(scaleX, scaleY, scaleZ);
}

#pragma region BSP
bool ModelNodeTransform::getIsBSPPlane() { return isBSPPlane; }

void ModelNodeTransform::setBSPPlane(Plane * _bspPlane)
{
	if (bspPlane) delete bspPlane;
	bspPlane = _bspPlane;

	isBSPPlane = true;
}

void ModelNodeTransform::eraseBSPPlane()
{
	if (bspPlane)
	{
		delete bspPlane;
		bspPlane = NULL;
	}

	isBSPPlane = false;
}

Plane* ModelNodeTransform::getBSPPlane() { return bspPlane; }
#pragma endregion