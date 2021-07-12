#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "Tools/Includes.h"
#include "../Entity.h"
#include "Renderer/Renderer.h"
#include "Mesh/Mesh.h"
#include "ModelNode/ModelNode.h"

using namespace std;

class GENGINE_API Model : public Entity
{
	string directory;

	ModelNode* rootNode = NULL;
public:
	Model(string _directory, ModelNode* _rootNode);
	~Model();

	string getDirectory();
	ModelNode* getRootNode();

	void draw() override;
};

#endif // !MODEL_H