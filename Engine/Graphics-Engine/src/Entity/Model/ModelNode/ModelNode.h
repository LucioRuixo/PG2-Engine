#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <string>
#include <vector>
#include "Tools/Includes.h"
#include "Entity/Model/Mesh/Mesh.h"

using namespace std;

class GENGINE_API ModelNode : public Entity
{
	string name;

	vector<Mesh*> meshes;
public:
	ModelNode(string _name, vector<Mesh*> _meshes);
	~ModelNode();

	string getName();

	void draw() override;
};

#endif // !MODEL_NODE_H