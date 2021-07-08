#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include "Tools/Includes.h"
#include "Entity/Model/Mesh/Mesh.h"

using namespace std;

class GENGINE_API Node
{
	string name;

	vector<Mesh*> meshes;
	vector<Node*> children;
public:
	Node(string _name, vector<Mesh*> _meshes);
	Node(string _name, vector<Mesh*> _meshes, vector<Node*> _children);
	~Node();

	string getName();
	vector<Node*> getChildren();
	void addChild(Node* child);

	void draw(mat4 model);
};

#endif // !NODE_H