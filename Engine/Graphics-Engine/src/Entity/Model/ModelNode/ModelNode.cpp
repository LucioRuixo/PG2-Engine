#include "ModelNode.h"

ModelNode::ModelNode(string _name, vector<Mesh*> _meshes, vector<Entity*> _children) : Entity()
{
	name = _name;
	meshes = _meshes;

	for (int i = 0; i < _children.size(); i++) addChild(_children[i]);

	generateCollisonBox();

	if (name.substr(0, 3) == "BSP" && meshes.size() > 0)
	{
		vec3 position = Entity::transform->getPosition();
		vec3 normal = mat3(transpose(inverse(Entity::transform->getGlobalModel()))) * meshes[0]->getVertices()[0].Normal;
		Plane* bspPlane = new Plane(normal);

		transform = new ModelNodeTransform(bspPlane);
	}
	else transform = new ModelNodeTransform();
}

ModelNode::~ModelNode()
{
	if (transform) delete transform;

	if (!meshes.empty()) meshes.clear();
}

void ModelNode::generateCollisonBox()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		vector<Vertex> vertices = meshes[i]->getVertices();

		for (int j = 0; j < vertices.size(); j++)
		{
			collisionBox.minEdge.x = glm::min(collisionBox.minEdge.x, vertices[j].Position.x);
			collisionBox.minEdge.y = glm::min(collisionBox.minEdge.y, vertices[j].Position.y);
			collisionBox.minEdge.z = glm::min(collisionBox.minEdge.z, vertices[j].Position.z);

			collisionBox.maxEdge.x = glm::max(vertices[j].Position.x, collisionBox.maxEdge.x);
			collisionBox.maxEdge.y = glm::max(vertices[j].Position.y, collisionBox.maxEdge.y);
			collisionBox.maxEdge.z = glm::max(vertices[j].Position.z, collisionBox.maxEdge.z);
		}
	}

	cout << "children: " << children.size() << endl;
	for (int k = 0; k < children.size(); k++)
	{
		ModelNode* child = dynamic_cast<ModelNode*>(children[k]);

		cout << "child min edgdes: " << child->getRawCollisionBox().minEdge.x << " | " << child->getRawCollisionBox().minEdge.y << " | " << child->getRawCollisionBox().minEdge.z << endl;
		cout << "child max edgdes: " << child->getRawCollisionBox().maxEdge.x << " | " << child->getRawCollisionBox().maxEdge.y << " | " << child->getRawCollisionBox().maxEdge.z << endl;

		collisionBox.minEdge.x = glm::min(collisionBox.minEdge.x, child->getRawCollisionBox().minEdge.x);
		collisionBox.minEdge.y = glm::min(collisionBox.minEdge.y, child->getRawCollisionBox().minEdge.y);
		collisionBox.minEdge.z = glm::min(collisionBox.minEdge.z, child->getRawCollisionBox().minEdge.z);

		collisionBox.maxEdge.x = glm::max(child->getRawCollisionBox().maxEdge.x, collisionBox.maxEdge.x);
		collisionBox.maxEdge.y = glm::max(child->getRawCollisionBox().maxEdge.y, collisionBox.maxEdge.y);
		collisionBox.maxEdge.z = glm::max(child->getRawCollisionBox().maxEdge.z, collisionBox.maxEdge.z);
	}

	cout << "min edgdes: " << collisionBox.minEdge.x << " | " << collisionBox.minEdge.y << " | " << collisionBox.minEdge.z << endl;
	cout << "max edgdes: " << collisionBox.maxEdge.x << " | " << collisionBox.maxEdge.y << " | " << collisionBox.maxEdge.z << endl;
}

void ModelNode::updateModels(mat4 otherModel)
{
	transform->updateGlobalModel(otherModel);

	for (int i = 0; i < children.size(); i++) dynamic_cast<ModelNode*>(children[i])->updateModels(otherModel);
}

string ModelNode::getName() { return name; }

CollisionBox ModelNode::getRawCollisionBox() { return collisionBox; }

CollisionBox ModelNode::getCollisionBox()
{
	CollisionBox transformedCollisionBox;
	transformedCollisionBox.minEdge = (collisionBox.minEdge + transform->getPosition()) * transform->getScale();
	transformedCollisionBox.maxEdge = (collisionBox.maxEdge + transform->getPosition()) * transform->getScale();

	return transformedCollisionBox;
}

ModelNodeTransform * ModelNode::getTransform() { return transform; }

void ModelNode::draw()
{
	renderer->setModel(renderer->getShaderProgram(shader), transform->getGlobalModel());
	for (int i = 0; i < meshes.size(); i++) if (meshes[i]) meshes[i]->draw();

	if (transform->getIsBSPPlane()) transform->getBSPPlane()->draw();

	Entity::draw();
}