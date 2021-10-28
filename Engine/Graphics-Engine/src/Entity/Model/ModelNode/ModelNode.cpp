#include "ModelNode.h"

ModelNode::ModelNode(string _name, vector<Mesh*> _meshes) : Entity()
{
	name = _name;
	meshes = _meshes;

	if (name.substr(0, 3) == "BSP" && meshes.size() > 0)
	{
		vec3 position = Entity::transform->getPosition();
		vec3 normal = mat3(transpose(inverse(Entity::transform->getGlobalModel()))) * meshes[0]->getVertices()[0].Normal;
		Plane* bspPlane = new Plane(position, normal);

		transform = new ModelNodeTransform(bspPlane);
	}
	else transform = new ModelNodeTransform();
}

ModelNode::~ModelNode()
{
	if (transform) delete transform;

	if (!meshes.empty()) meshes.clear();
}

void ModelNode::updateModels(mat4 otherModel)
{
	transform->updateGlobalModel(otherModel);

	for (int i = 0; i < children.size(); i++) dynamic_cast<ModelNode*>(children[i])->updateModels(otherModel);
}

string ModelNode::getName() { return name; }

ModelNodeTransform * ModelNode::getTransform() { return transform; }

void ModelNode::draw()
{
	renderer->setModel(renderer->getShaderProgram(shader), transform->getGlobalModel());
	for (int i = 0; i < meshes.size(); i++) if (meshes[i]) meshes[i]->draw();

	if (transform->getIsBSPPlane()) transform->getBSPPlane()->draw();

	Entity::draw();
}