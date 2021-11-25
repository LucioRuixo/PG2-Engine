#include "ModelNodeTransform.h"

ModelNodeTransform::ModelNodeTransform() : Transform() {}

ModelNodeTransform::ModelNodeTransform(Plane* _bspPlane) : Transform()
{
	if (_bspPlane)
	{
		setBSPPlane(_bspPlane);
		rotate(-90.0f, 0.0f, 0.0f);
		transformData.rotation.x += 90.0f;
	}
}

ModelNodeTransform::~ModelNodeTransform() {}

void ModelNodeTransform::initializeValues(vec3 _position, vec3 _rotation, vec3 _scale)
{
	transformData.position = _position;
	transformData.rotation = _rotation;
	transformData.scale = _scale;
}

void ModelNodeTransform::processRotation(float pitch, float yaw, float roll)
{
	transformData.rotation.x += pitch;
	transformData.rotation.y += yaw;
	transformData.rotation.z += roll;

	if (transformData.rotation.x >= 360.0f) transformData.rotation.x -= 360.0f;
	else if (transformData.rotation.x < 0.0f) transformData.rotation.x += 360.0f;

	if (transformData.rotation.y >= 360.0f) transformData.rotation.y -= 360.0f;
	else if (transformData.rotation.y < 0.0f) transformData.rotation.y += 360.0f;

	if (transformData.rotation.z >= 360.0f) transformData.rotation.z -= 360.0f;
	else if (transformData.rotation.z < 0.0f) transformData.rotation.z += 360.0f;

	localModel.rotation = glm::rotate(localModel.rotation, radians(pitch), vec3(1.0f, 0.0f, 0.0f));
	localModel.rotation = glm::rotate(localModel.rotation, radians(yaw), vec3(0.0f, 1.0f, 0.0f));
	localModel.rotation = glm::rotate(localModel.rotation, radians(roll), vec3(0.0f, 0.0f, 1.0f));

	updateLocalModel();
	updateDirectionVectors(pitch, yaw, roll);
}

void ModelNodeTransform::updateLocalModel()
{
	localModel.model = localModel.translation * localModel.rotation * localModel.scale;

	updateGlobalModel();
}

void ModelNodeTransform::updateGlobalModel()
{
	if (parent) globalModel = parent->getGlobalModel() * localModel.model;
	else globalModel = localModel.model;

	transformedSinceCBUpdate = true;

	if (!children.empty()) for (int i = 0; i < children.size(); i++)
	{
		ModelNodeTransform* child = dynamic_cast<ModelNodeTransform*>(children[i]);

		if (child) child->updateGlobalModel();
		else children[i]->updateGlobalModel();
	}
}

void ModelNodeTransform::updateGlobalModel(mat4 other) { globalModel = other * localModel.model; }

void ModelNodeTransform::setTransformedSinceCBUpdate(bool _transformedSinceCBUpdate) { transformedSinceCBUpdate = _transformedSinceCBUpdate; }
bool ModelNodeTransform::getTransformedSinceCBUpdate() { return transformedSinceCBUpdate; }

#pragma region Transformations
void ModelNodeTransform::translate(float x, float y, float z)
{
	transformData.position.x += x;
	transformData.position.y += y;
	transformData.position.z += z;

	vec3 position = transformData.position;
	position.x *= -1.0f;
	localModel.translation = glm::translate(mat4(1.0f), position);

	updateLocalModel();
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
	if (pitch != 0.0f) processRotation(pitch, 0.0f, 0.0f);
	if (yaw != 0.0f) processRotation(0.0f, yaw, 0.0f);
	if (roll != 0.0f) processRotation(0.0f, 0.0f, roll);
}

void ModelNodeTransform::setRotation(float pitch, float yaw, float roll)
{
	float rotationX = positiveDegrees(pitch - transformData.rotation.x);
	float rotationY = positiveDegrees(yaw - transformData.rotation.y);
	float rotationZ = positiveDegrees(roll - transformData.rotation.z);

	if (rotationX != 0.0f) processRotation(rotationX, 0.0f, 0.0f);
	if (rotationY != 0.0f) processRotation(0.0f, rotationY, 0.0f);
	if (rotationZ != 0.0f) processRotation(0.0f, 0.0f, rotationZ);
}

void ModelNodeTransform::scale(float x, float y, float z)
{
	transformData.scale.x += x;
	transformData.scale.y += y;
	transformData.scale.z += z;

	localModel.scale = glm::scale(mat4(1.0f), transformData.scale);
	updateLocalModel();
}

void ModelNodeTransform::setScale(float x, float y, float z)
{
	float scaleX = x - transformData.scale.x;
	float scaleY = y - transformData.scale.y;
	float scaleZ = z - transformData.scale.z;

	scale(scaleX, scaleY, scaleZ);
}
#pragma endregion

#pragma region BSP
bool ModelNodeTransform::getIsBSPPlane() { return isBSPPlane; }

void ModelNodeTransform::setBSPPlane(Plane* _bspPlane)
{
	if (bspPlane)
	{
		removeChild(bspPlane->getTransform());
		delete bspPlane;
	}

	bspPlane = _bspPlane;

	addChild(bspPlane->getTransform());
	bspPlane->getTransform()->setPosition(0.0f, 0.0f, 0.0f);
	bspPlane->getTransform()->setRotation(0.0f, 0.0f, 0.0f);

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