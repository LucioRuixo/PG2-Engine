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

void ModelNodeTransform::updateGlobalModel(mat4 other) { globalModel = other * localModel.model; }

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