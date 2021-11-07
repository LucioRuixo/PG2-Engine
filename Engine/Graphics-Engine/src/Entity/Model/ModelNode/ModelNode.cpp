#include "ModelNode.h"

ModelNode::ModelNode(string _name, bool _isRoot, vector<Mesh*> _meshes, vector<Entity*> _children) : Entity()
{
	name = _name;
	isRoot = _isRoot;
	meshes = _meshes;

	generateCollisonBox();

	if (name.substr(0, 3) == "BSP" && meshes.size() > 0)
	{
		vec3 position = Entity::transform->getPosition();
		vec3 normal = mat3(transpose(inverse(Entity::transform->getGlobalModel()))) * meshes[0]->getVertices()[0].Normal;
		Plane* bspPlane = new Plane();

		transform = new ModelNodeTransform(bspPlane);
	}
	else transform = new ModelNodeTransform();

	for (int i = 0; i < _children.size(); i++) addChild(_children[i]);
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

	for (int k = 0; k < children.size(); k++)
	{
		ModelNode* child = dynamic_cast<ModelNode*>(children[k]);

		collisionBox.minEdge.x = glm::min(collisionBox.minEdge.x, child->getRawCollisionBox().minEdge.x);
		collisionBox.minEdge.y = glm::min(collisionBox.minEdge.y, child->getRawCollisionBox().minEdge.y);
		collisionBox.minEdge.z = glm::min(collisionBox.minEdge.z, child->getRawCollisionBox().minEdge.z);

		collisionBox.maxEdge.x = glm::max(child->getRawCollisionBox().maxEdge.x, collisionBox.maxEdge.x);
		collisionBox.maxEdge.y = glm::max(child->getRawCollisionBox().maxEdge.y, collisionBox.maxEdge.y);
		collisionBox.maxEdge.z = glm::max(child->getRawCollisionBox().maxEdge.z, collisionBox.maxEdge.z);
	}

	//cout << "min edgdes: " << collisionBox.minEdge.x << " | " << collisionBox.minEdge.y << " | " << collisionBox.minEdge.z << endl;
	//cout << "max edgdes: " << collisionBox.maxEdge.x << " | " << collisionBox.maxEdge.y << " | " << collisionBox.maxEdge.z << endl;
}

void ModelNode::processBSP(bool shouldBeDrawn, vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes)
{
	if (isRoot)
	{
		drawMeshes();
		drawChildrenAsBSPNode(shouldBeDrawn, cameraPosition, planes, drawPlanes);

		return;
	}

	if (transform->getIsBSPPlane())
	{
		if (drawPlanes)
		{
			drawMeshes();
			transform->getBSPPlane()->draw();
		}

		drawChildrenAsBSPNode(shouldBeDrawn, cameraPosition, planes, drawPlanes);
	}
	else
	{
		bool draw = false;

		if (shouldBeDrawn)
		{
			for (int i = 0; i < planes.size(); i++)
			{
				if (planes[i]->sameSide(cameraPosition, getCollisionBoxVertices()))
				{
					draw = true;
					break;
				}
			}
		}

		if (draw)
		{
			//cout << "drawing " << name << endl;
			drawMeshes();
		}
		//else cout << "NOT drawing " << name << endl;

		drawChildrenAsBSPNode(draw, cameraPosition, planes, drawPlanes);
	}
}

void ModelNode::drawChildrenAsBSPNode(bool shouldBeDrawn, vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes)
{
	for (int i = 0; i < children.size(); i++) dynamic_cast<ModelNode*>(children[i])->drawAsBSPNode(cameraPosition, planes, drawPlanes);
}

void ModelNode::updateModels(mat4 otherModel)
{
	transform->updateGlobalModel(otherModel);

	for (int i = 0; i < children.size(); i++) dynamic_cast<ModelNode*>(children[i])->updateModels(otherModel);
}

string ModelNode::getName() { return name; }

bool ModelNode::getIsRoot() { return isRoot; }

CollisionBox ModelNode::getRawCollisionBox() { return collisionBox; }

CollisionBox ModelNode::getCollisionBox()
{
	CollisionBox transformedCollisionBox;
	transformedCollisionBox.minEdge = (collisionBox.minEdge + transform->getPosition()) * transform->getScale();
	transformedCollisionBox.maxEdge = (collisionBox.maxEdge + transform->getPosition()) * transform->getScale();

	return transformedCollisionBox;
}

vec3* ModelNode::getCollisionBoxVertices()
{
	//0 ---
	//1 +--
	//2 ++-
	//3 -+-
	//4 --+
	//5 +-+
	//6 +++
	//7 -++
	vec3 vertices[8]
	{
		vec3(collisionBox.minEdge.x, collisionBox.minEdge.y, collisionBox.minEdge.z),
		vec3(collisionBox.maxEdge.x, collisionBox.minEdge.y, collisionBox.minEdge.z),
		vec3(collisionBox.maxEdge.x, collisionBox.maxEdge.y, collisionBox.minEdge.z),
		vec3(collisionBox.minEdge.x, collisionBox.maxEdge.y, collisionBox.minEdge.z),
		vec3(collisionBox.minEdge.x, collisionBox.minEdge.y, collisionBox.maxEdge.z),
		vec3(collisionBox.maxEdge.x, collisionBox.minEdge.y, collisionBox.maxEdge.z),
		vec3(collisionBox.maxEdge.x, collisionBox.maxEdge.y, collisionBox.maxEdge.z),
		vec3(collisionBox.minEdge.x, collisionBox.maxEdge.y, collisionBox.maxEdge.z)
	};

	return vertices;
}

ModelNodeTransform * ModelNode::getTransform() { return transform; }

#pragma region Children
void ModelNode::addChild(Entity* child)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] == child)
		{
			cout << "Entity intended to be added to parent is already a child" << endl;

			return;
		}
	}

	children.push_back(child);
	child->setParent(this);

	transform->addChild(child->getTransform());
}

void ModelNode::removeChild(Entity* child)
{
	vector<Entity*>::iterator iterator;
	for (iterator = children.begin(); iterator < children.end(); iterator++)
	{
		if (*iterator == child)
		{
			children.erase(iterator);
			transform->removeChild(child->getTransform());
			child->setParent(NULL);

			return;
		}
	}

	cout << "Child entity intended to be removed from parent was not found" << endl;
}
#pragma endregion

void ModelNode::drawMeshes()
{
	setUniformValues();
	renderer->setModel(renderer->getShaderProgram(shader), transform->getGlobalModel());

	for (int i = 0; i < meshes.size(); i++) if (meshes[i]) meshes[i]->draw();
}

void ModelNode::draw()
{
	drawMeshes();
	if (transform->getIsBSPPlane()) transform->getBSPPlane()->draw();

	Entity::draw();
}

void ModelNode::drawAsBSPNode(vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes) { processBSP(true, cameraPosition, planes, drawPlanes); }