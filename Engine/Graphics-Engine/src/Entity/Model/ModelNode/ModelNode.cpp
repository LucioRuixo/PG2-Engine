#include "ModelNode.h"

ModelNode::ModelNode(string _name, vector<Mesh*> _meshes) : Entity()
{
	name = _name;
	meshes = _meshes;

	if (name.substr(0, 3) == "BSP" && meshes.size() > 0) isBSPPlane = true;
}

ModelNode::~ModelNode()
{
	if (transform) delete transform;

	if (!meshes.empty()) meshes.clear();
}

string ModelNode::getName() { return name; }

#pragma region BSP
bool ModelNode::getIsBSPPlane() { return isBSPPlane; }

vec3 ModelNode::getBSPNornal()
{
	if (!isBSPPlane)
	{
		cout << "Model node is not a valid BSP Plane. Returning (0, 0, 0)..." << endl;
		return vec3(0.0f);
	}

	return mat3(transpose(inverse(transform->getGlobalModel()))) * meshes[0]->getVertices()[0].Normal;
}
#pragma endregion

void ModelNode::draw()
{
	renderer->setModel(renderer->getShaderProgram(shader), transform->getGlobalModel());
	for (int i = 0; i < meshes.size(); i++) if (meshes[i]) meshes[i]->draw();

	Entity::draw();
}