#include "ModelNode.h"

ModelNode::ModelNode(string _name, bool _isRoot, vector<Mesh*> _meshes, vector<Entity*> _children) : Entity()
{
	name = _name;
	isRoot = _isRoot;
	meshes = _meshes;

	setUpCollisionBox();

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

void ModelNode::setUpCollisionBox()
{
	CollisionBoxEdges edges;
	if (meshes.size() > 0)
	{
		edges.minEdge.x = meshes[0]->getVertices()[0].Position.x;
		edges.minEdge.y = meshes[0]->getVertices()[0].Position.y;
		edges.minEdge.z = meshes[0]->getVertices()[0].Position.z;

		edges.maxEdge.x = meshes[0]->getVertices()[0].Position.x;
		edges.maxEdge.y = meshes[0]->getVertices()[0].Position.y;
		edges.maxEdge.z = meshes[0]->getVertices()[0].Position.z;
	}

	for (int i = 0; i < meshes.size(); i++)
	{
		vector<Vertex> vertices = meshes[i]->getVertices();

		for (int j = 0; j < vertices.size(); j++)
		{
			edges.minEdge.x = glm::min(edges.minEdge.x, vertices[j].Position.x);
			edges.minEdge.y = glm::min(edges.minEdge.y, vertices[j].Position.y);
			edges.minEdge.z = glm::min(edges.minEdge.z, vertices[j].Position.z);

			edges.maxEdge.x = glm::max(vertices[j].Position.x, edges.maxEdge.x);
			edges.maxEdge.y = glm::max(vertices[j].Position.y, edges.maxEdge.y);
			edges.maxEdge.z = glm::max(vertices[j].Position.z, edges.maxEdge.z);
		}
	}

	collisionBoxVertices = generateCollisonBoxVertices(edges);
}

vector<vec3> ModelNode::generateCollisonBoxVertices(CollisionBoxEdges edges)
{
	vector<vec3> vertices = vector<vec3>
	{
		vec3(edges.minEdge.x, edges.minEdge.y, edges.minEdge.z), //0 ---
		vec3(edges.maxEdge.x, edges.minEdge.y, edges.minEdge.z), //1 +--
		vec3(edges.maxEdge.x, edges.maxEdge.y, edges.minEdge.z), //2 ++-
		vec3(edges.minEdge.x, edges.maxEdge.y, edges.minEdge.z), //3 -+-
		vec3(edges.minEdge.x, edges.minEdge.y, edges.maxEdge.z), //4 --+
		vec3(edges.maxEdge.x, edges.minEdge.y, edges.maxEdge.z), //5 +-+
		vec3(edges.maxEdge.x, edges.maxEdge.y, edges.maxEdge.z), //6 +++
		vec3(edges.minEdge.x, edges.maxEdge.y, edges.maxEdge.z)  //7 -++
	};

	return vertices;
}

CollisionBoxEdges ModelNode::generateCollisonBoxEdges(vector<vec3> vertices)
{
	CollisionBoxEdges edges;
	if (vertices.size() > 0)
	{
		edges.minEdge.x = vertices[0].x;
		edges.minEdge.y = vertices[0].y;
		edges.minEdge.z = vertices[0].z;

		edges.maxEdge.x = vertices[0].x;
		edges.maxEdge.y = vertices[0].y;
		edges.maxEdge.z = vertices[0].z;
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		edges.minEdge.x = glm::min(edges.minEdge.x, vertices[i].x);
		edges.minEdge.y = glm::min(edges.minEdge.y, vertices[i].y);
		edges.minEdge.z = glm::min(edges.minEdge.z, vertices[i].z);

		edges.maxEdge.x = glm::max(vertices[i].x, edges.maxEdge.x);
		edges.maxEdge.y = glm::max(vertices[i].y, edges.maxEdge.y);
		edges.maxEdge.z = glm::max(vertices[i].z, edges.maxEdge.z);
	}

	return edges;
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
		bool draw = true;

		if (shouldBeDrawn)
		{
			//cout << endl;
			for (int i = 0; i < planes.size(); i++)
			{
				if (!planes[i]->sameSide(cameraPosition, getCollisionBoxVertices()))
				{
					draw = false;
					break;
				}
			}
		}

		//cout << (draw ? "draw" : "DON'T draw") << endl;
		if (draw) drawMeshes();
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

CollisionBoxEdges ModelNode::getRawCollisionBox() { return collisionBoxEdges; }

CollisionBoxEdges ModelNode::getCollisionBox()
{
	CollisionBoxEdges transformedCollisionBox;

	vec4 minEdge = transform->getGlobalModel() * vec4(collisionBoxEdges.minEdge, 1.0f);
	vec4 maxEdge = transform->getGlobalModel() * vec4(collisionBoxEdges.maxEdge, 1.0f);
	transformedCollisionBox.minEdge = vec3(-minEdge.x, minEdge.y, minEdge.z);
	transformedCollisionBox.maxEdge = vec3(-maxEdge.x, maxEdge.y, maxEdge.z);

	return transformedCollisionBox;
}

vector<vec3> ModelNode::getCollisionBoxVertices()
{
	vector<vec3> transformedVertices;
	for (int i = 0; i < collisionBoxVertices.size(); i++)
	{
		vec4 vertex = transform->getGlobalModel() * vec4(collisionBoxVertices[i], 1.0f);
		transformedVertices.push_back(vec3(-vertex.x, vertex.y, vertex.z));
	}

	if (children.size() > 0)
	{
		CollisionBoxEdges transformedEdges = generateCollisonBoxEdges(transformedVertices);
		for (int i = 0; i < children.size(); i++)
		{
			vector<vec3> childVertices = dynamic_cast<ModelNode*>(children[i])->getCollisionBoxVertices();
			CollisionBoxEdges childEdges = generateCollisonBoxEdges(childVertices);

			transformedEdges.minEdge.x = glm::min(transformedEdges.minEdge.x, childEdges.minEdge.x);
			transformedEdges.minEdge.y = glm::min(transformedEdges.minEdge.y, childEdges.minEdge.y);
			transformedEdges.minEdge.z = glm::min(transformedEdges.minEdge.z, childEdges.minEdge.z);

			transformedEdges.maxEdge.x = glm::max(childEdges.maxEdge.x, transformedEdges.maxEdge.x);
			transformedEdges.maxEdge.y = glm::max(childEdges.maxEdge.y, transformedEdges.maxEdge.y);
			transformedEdges.maxEdge.z = glm::max(childEdges.maxEdge.z, transformedEdges.maxEdge.z);
		}

		return generateCollisonBoxVertices(transformedEdges);
	}
	else return transformedVertices;
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
	//if (transform->getIsBSPPlane()) transform->getBSPPlane()->draw();

	Entity::draw();
}

void ModelNode::drawAsBSPNode(vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes) { processBSP(true, cameraPosition, planes, drawPlanes); }