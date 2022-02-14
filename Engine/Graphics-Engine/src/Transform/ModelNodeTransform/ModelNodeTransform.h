#ifndef MODEL_NODE_TRANSFORM_H
#define MODEL_NODE_TRANSFORM_H

#include "Tools/Includes.h"
#include "Transform/Transform.h"
#include "Entity/Plane/Plane.h"

class GENGINE_API ModelNodeTransform : public Transform
{
	bool isBSPPlane = false;
	Plane* bspPlane = NULL;

protected:
	void processRotation(float pitch, float yaw, float roll, bool matchingParentRotation) override;

public:
	ModelNodeTransform();
	ModelNodeTransform(Plane* _bspPlane);
	~ModelNodeTransform();

	void initializeValues(vec3 _position, vec3 _rotation, vec3 _scale);
	void updateLocalModel() override;
	void updateGlobalModel() override;
	void updateGlobalModel(mat4 other) override;

//#pragma region Transformations
//	void translate(float x, float y, float z) override;
//	void setPosition(float x, float y, float z) override;
//	void rotate(float pitch, float yaw, float roll) override;
//	void setRotation(float pitch, float yaw, float roll) override;
//	void scale(float x, float y, float z) override;
//	void setScale(float x, float y, float z) override;
//#pragma endregion

#pragma region BSP
	bool getIsBSPPlane();
	void setBSPPlane(Plane* _bspPlane);
	void eraseBSPPlane();
	Plane* getBSPPlane();
#pragma endregion
};

#endif // !MODEL_NODE_TRANSFORM