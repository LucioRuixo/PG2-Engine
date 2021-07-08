#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "Tools/Includes.h"
#include "../Entity.h"
#include "Renderer/Renderer.h"
#include "Mesh/Mesh.h"
#include "Node/Node.h"

using namespace std;

class GENGINE_API Model : public Entity
{
	string directory;

	Node* rootNode = NULL;
public:
	Model(string _directory, Node* _rootNode);
	~Model();

	string getDirectory();
	Node* getRootNode();

	void draw();
};

#endif // !MODEL_H