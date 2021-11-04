#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <string>
#include <vector>
#include "Tools/Includes.h"
#include "Entity/Plane/Plane.h"
#include "Entity/Model/Mesh/Mesh.h"
#include "Transform/ModelNodeTransform/ModelNodeTransform.h"

using namespace std;

struct CollisionBox
{
	vec3 minEdge = vec3(0.0f);
	vec3 maxEdge = vec3(0.0f);
};

class GENGINE_API ModelNode : public Entity
{
	string name;

	CollisionBox collisionBox;
	ModelNodeTransform* transform;

	vector<Mesh*> meshes;

	void generateCollisonBox();
public:
	ModelNode(string _name, vector<Mesh*> _meshes, vector<Entity*> _children);
	~ModelNode();

	void updateModels(mat4 otherModel) override;

	string getName();
	CollisionBox getRawCollisionBox();
	CollisionBox getCollisionBox();
	ModelNodeTransform* getTransform() override;

	void draw() override;
};

#endif // !MODEL_NODE_H