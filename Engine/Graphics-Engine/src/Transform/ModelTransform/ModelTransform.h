#ifndef MODEL_TRANSFORM_H
#define MODEL_TRANSFORM_H

#include "Tools/Includes.h"
#include "Transform/Transform.h"
#include "Entity/Model/ModelNode/ModelNode.h"

class GENGINE_API ModelTransform : public Transform
{
	ModelNode* rootNode = NULL;
public:
	ModelTransform(ModelNode* _rootNode);
	~ModelTransform();

	void translate(float x, float y, float z) override;
	void setPosition(float x, float y, float z) override;
	void rotate(float pitch, float yaw, float roll) override;
	void setRotation(float pitch, float yaw, float roll) override;
	void scale(float x, float y, float z) override;
	void setScale(float x, float y, float z) override;
};

#endif // !MODEL_TRANSFORM