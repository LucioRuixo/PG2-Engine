#include "ModelNode.h"

ModelNode::ModelNode(string _name, vector<Mesh*> _meshes)
{
	name = _name;
	meshes = _meshes;
}

//ModelNode::ModelNode(string _name, vector<Mesh*> _meshes, vector<ModelNode*> _children)
//{
//	name = _name;
//	meshes = _meshes;
//	children = _children;
//}

ModelNode::~ModelNode()
{
	if (transform) delete transform;

	if (!meshes.empty()) meshes.clear();

	//if (!children.empty())
	//{
	//	for (int i = 0; i < children.size(); i++) if (children[i]) delete children[i];
	//	children.clear();
	//}
}

string ModelNode::getName() { return name; }

//vector<ModelNode*> ModelNode::getChildren() { return children; }
//
//void ModelNode::addChild(ModelNode* child) { children.push_back(child); }

void ModelNode::draw()
{
	for (int i = 0; i < meshes.size(); i++) if (meshes[i]) meshes[i]->draw();

	Entity::draw();
	//for (int i = 0; i < children.size(); i++) if (children[i]) children[i]->draw();
}