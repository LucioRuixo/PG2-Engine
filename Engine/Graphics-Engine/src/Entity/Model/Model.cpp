#include "Model.h"

Model::Model(string _directory, ModelNode* _rootNode)
{
	directory = _directory;
	rootNode = _rootNode;
}

Model::Model(string _directory, ModelNode * _rootNode, vector<Plane*> _bspPlanes)
{
	directory = _directory;
	rootNode = _rootNode;

	bspPlanes = _bspPlanes;
	isBSPScene = true;
}

Model::~Model() { if (rootNode) delete rootNode; }

string Model::getDirectory() { return directory; }

ModelNode* Model::getRootNode() { return rootNode; }

bool Model::getIsBSPScene() { return isBSPScene; }

void Model::draw() { rootNode->draw(); }

void Model::drawAsBSPScene(vec3 cameraPosition, bool drawPlanes)
{
	if (bspPlanes.size() > 0) rootNode->drawAsBSPNode(cameraPosition, bspPlanes, drawPlanes);
	else draw();
}