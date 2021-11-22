#ifndef MODEL_H
#define MODEL_H

#include "Tools/Includes.h"
#include "../Entity.h"
#include "Renderer/Renderer.h"
#include "Mesh/Mesh.h"
#include "ModelNode/ModelNode.h"

using namespace std;

class GENGINE_API Model
{
	string directory;
	bool isBSPScene = false;

	vector<Plane*> bspPlanes;

	ModelNode* rootNode = NULL;
public:
	Model(string _directory, ModelNode* _rootNode);
	Model(string _directory, ModelNode* _rootNode, vector<Plane*> _bspPlanes);
	~Model();

	string getDirectory();
	ModelNode* getRootNode();

	bool getIsBSPScene();

	void draw();
	void drawAsBSPScene(vec3 cameraPosition, bool drawPlanes);
};

#endif // !MODEL_H