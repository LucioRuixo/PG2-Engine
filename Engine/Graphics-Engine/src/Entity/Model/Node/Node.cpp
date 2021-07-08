#include "Node.h"

Node::Node(string _name, vector<Mesh*> _meshes)
{
	name = _name;
	meshes = _meshes;
}

Node::Node(string _name, vector<Mesh*> _meshes, vector<Node*> _children)
{
	name = _name;
	meshes = _meshes;
	children = _children;
}

Node::~Node()
{
	if (!meshes.empty()) meshes.clear();

	if (!children.empty())
	{
		for (int i = 0; i < children.size(); i++) if (children[i]) delete children[i];
		children.clear();
	}
}

string Node::getName() { return name; }

vector<Node*> Node::getChildren() { return children; }

void Node::addChild(Node* child) { children.push_back(child); }

void Node::draw(mat4 model)
{
	for (int i = 0; i < meshes.size(); i++) if (meshes[i]) meshes[i]->draw(model);

	for (int i = 0; i < children.size(); i++) if (children[i]) children[i]->draw(model);
}