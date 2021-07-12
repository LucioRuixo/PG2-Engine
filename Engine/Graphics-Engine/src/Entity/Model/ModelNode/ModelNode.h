#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <string>
#include <vector>
#include "Tools/Includes.h"
#include "Entity/Model/Mesh/Mesh.h"

using namespace std;

class GENGINE_API ModelNode : public Entity
{
	string name;

	vector<Mesh*> meshes;
	//vector<ModelNode*> children;
public:
	ModelNode(string _name, vector<Mesh*> _meshes);
	//ModelNode(string _name, vector<Mesh*> _meshes, vector<ModelNode*> _children);
	~ModelNode();

	string getName();
	//vector<ModelNode*> getChildren();
	//void addChild(ModelNode* child);

	void draw() override;
};

#endif // !MODEL_NODE_H