#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <string>
#include <vector>
#include "Tools/Includes.h"
#include "Entity/Plane/Plane.h"
#include "Entity/Model/Mesh/Mesh.h"
#include "Transform/ModelNodeTransform/ModelNodeTransform.h"

using namespace std;

class GENGINE_API ModelNode : public Entity
{
	string name;

	ModelNodeTransform* transform;

	vector<Mesh*> meshes;
public:
	ModelNode(string _name, vector<Mesh*> _meshes);
	~ModelNode();

	void updateModels(mat4 otherModel) override;

	string getName();
	ModelNodeTransform* getTransform() override;

	void draw() override;
};

#endif // !MODEL_NODE_H