#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "Tools/Includes.h"
#include "../Entity.h"
#include "Renderer/Renderer.h"
#include "Mesh/Mesh.h"
#include "ModelNode/ModelNode.h"
#include "Transform/ModelTransform/ModelTransform.h"

using namespace std;

class GENGINE_API Model// : public Entity
{
	string directory;
	bool isBSPScene = false;

	vector<Plane*> bspPlanes;

	ModelNode* rootNode = NULL;
	ModelTransform* transform;
public:
	Model(string _directory, ModelNode* _rootNode);
	Model(string _directory, ModelNode* _rootNode, vector<Plane*> _bspPlanes);
	~Model();

	string getDirectory();
	ModelNode* getRootNode();
	//ModelTransform* getTransform() override;

	bool getIsBSPScene();

	void draw();
	void drawAsBSPScene(vec3 cameraPosition, bool drawPlanes);
};

#endif // !MODEL_H