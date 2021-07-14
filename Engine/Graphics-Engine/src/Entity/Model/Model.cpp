#include "Model.h"

Model::Model(string _directory, ModelNode* _rootNode) : Entity()
{
	directory = _directory;
	rootNode = _rootNode;

	addChild(rootNode);

	//material.diffuseTexturesActive = true;
	//material.specularTexturesActive = true;
}

Model::~Model()
{
	if (rootNode) delete rootNode;
}

string Model::getDirectory() { return directory; }

ModelNode* Model::getRootNode() { return rootNode; }

void Model::draw()
{
	setUniformValues();

	//rootNode->draw();
	Entity::draw();
}