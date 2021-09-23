#include "Model.h"

Model::Model(string _directory, ModelNode* _rootNode) : Entity()
{
	directory = _directory;
	rootNode = _rootNode;

	transform = new ModelTransform(rootNode);

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

ModelTransform * Model::getTransform() { return transform; }

void Model::draw()
{
	setUniformValues();
	//renderer->setModel(renderer->getShaderProgram(shader), transform->getGlobalModel());
	//renderer->drawElements(vao, vbo, ebo, CUBE_INDICES);

	rootNode->draw();
	//Entity::draw();
}