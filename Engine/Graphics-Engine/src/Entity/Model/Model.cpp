#include "Model.h"

Model::Model(string _directory, Node* _rootNode) : Entity()
{
	directory = _directory;
	rootNode = _rootNode;

	material.diffuseTexturesActive = true;
	material.specularTexturesActive = true;
}

Model::~Model()
{
	if (rootNode) delete rootNode;
}

string Model::getDirectory() { return directory; }

Node * Model::getRootNode() { return rootNode; }

void Model::draw()
{
	setUniformValues();

	rootNode->draw(transform->getModel());
}