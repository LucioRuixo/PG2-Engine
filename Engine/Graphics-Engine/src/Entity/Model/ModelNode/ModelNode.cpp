#include "ModelNode.h"

ModelNode::ModelNode(string _name, vector<Mesh*> _meshes) : Entity()
{
	name = _name;
	meshes = _meshes;
}

ModelNode::~ModelNode()
{
	if (transform) delete transform;

	if (!meshes.empty()) meshes.clear();
}

string ModelNode::getName() { return name; }

//vector<ModelNode*> ModelNode::getChildren() { return children; }
//
//void ModelNode::addChild(ModelNode* child) { children.push_back(child); }

void ModelNode::draw()
{
	renderer->setModel(renderer->getShaderProgram(shader), transform->getGlobalModel());
	for (int i = 0; i < meshes.size(); i++) if (meshes[i]) meshes[i]->draw(/*transform->getModel()/*renderer, textureManager*/);

	Entity::draw();
	//for (int i = 0; i < children.size(); i++) if (children[i]) children[i]->draw();
}