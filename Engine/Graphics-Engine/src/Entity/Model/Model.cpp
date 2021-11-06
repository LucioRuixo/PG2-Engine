#include "Model.h"

Model::Model(string _directory, ModelNode* _rootNode) : Entity()
{
	directory = _directory;
	rootNode = _rootNode;

	transform = new ModelTransform(rootNode);

	addChild(rootNode);
}

Model::Model(string _directory, ModelNode * _rootNode, vector<Plane*> _bspPlanes)
{
	directory = _directory;
	rootNode = _rootNode;

	bspPlanes = _bspPlanes;
	isBSPScene = true;

	transform = new ModelTransform(rootNode);

	addChild(rootNode);
}

Model::~Model()
{
	if (rootNode) delete rootNode;
}

string Model::getDirectory() { return directory; }

ModelNode* Model::getRootNode() { return rootNode; }

ModelTransform * Model::getTransform() { return transform; }

bool Model::getIsBSPScene() { return isBSPScene; }

void Model::draw()
{
	setUniformValues();

	rootNode->draw();
}

void Model::drawAsBSPScene(vec3 cameraPosition, bool drawPlanes)
{
	if (bspPlanes.size() > 0)
	{
		setUniformValues();
		rootNode->drawAsBSPNode(cameraPosition, bspPlanes, drawPlanes);
	}
	else draw();
}