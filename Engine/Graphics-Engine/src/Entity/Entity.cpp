#include "Entity.h"

vector<Entity*> Entity::entities;
vector<Entity*> Entity::renderizableEntities;
Renderer* Entity::renderer = NULL;
TextureManager* Entity::textureManager = NULL;

bool Entity::planeRenderingDataInitialized = false;
vector<vec3> Entity::planeVertexPositions;

bool Entity::cubeRenderingDataInitialized = false;
vector<vec3> Entity::cubeVertexPositions;

Entity::Entity(bool _renderizable) { initialize(_renderizable); }

Entity::Entity(vector<Entity*> _children, bool _renderizable)
{
	initialize(_renderizable);

	for (int i = 0; i < _children.size(); i++) addChild(_children[i]);
}

Entity::Entity(vec3 _color, bool _renderizable)
{
	initialize(_renderizable);

	setColor(_color);
}

Entity::Entity(Material _material, bool _renderizable)
{
	initialize(_renderizable);

	setMaterial(_material);
}

Entity::Entity(vec3 _color, Material _material, bool _renderizable)
{
	initialize(_renderizable);

	setColor(_color);
	setMaterial(_material);
}

Entity::~Entity() { if (transform) delete transform; }

void Entity::initialize(bool _renderizable)
{
	entities.push_back(this);

	renderizable = _renderizable;
	if (renderizable)
	{
		renderizableEntities.push_back(this);
		cout << "new renderizable entity created, total: " << renderizableEntities.size() << endl;
	}
	else shouldBeDrawn = false;

	transform = new Transform();
}

vector<Entity*> Entity::getEntities() { return entities; }

vector<Entity*> Entity::getRenderizableEntities() { return renderizableEntities; }

#pragma region Collision Box
vector<vec3> Entity::transformVertices(vector<vec3> vertices)
{
	vector<vec3> transformedVertices;
	for (int i = 0; i < vertices.size(); i++)
	{
		vec3 vertex = vec3(transform->getGlobalModel() * vec4(vertices[i], 1.0f));
		vertex.x *= -1.0f;
		transformedVertices.push_back(vertex);
	}

	return transformedVertices;
}

vector<vec3> Entity::generateCBVertices(CollisionBoxEdges edges)
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

CollisionBoxEdges Entity::generateCBEdges(vector<vec3> vertices)
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

vector<vec3> Entity::calculateCollisionVertices(vector<vec3> vertices)
{
	if (transform->getTransformedSinceCBUpdate())
	{
		if (children.size() > 0)
		{
			vector<vec3> transformedVertices = getTransformedVertices(vertices);
			CollisionBoxEdges transformedEdges = generateCBEdges(transformedVertices);

			for (int i = 0; i < children.size(); i++)
			{
				vector<vec3> childVertices = dynamic_cast<Entity*>(children[i])->getCollisionVertices();
				CollisionBoxEdges childEdges = generateCBEdges(childVertices);

				transformedEdges.minEdge.x = glm::min(transformedEdges.minEdge.x, childEdges.minEdge.x);
				transformedEdges.minEdge.y = glm::min(transformedEdges.minEdge.y, childEdges.minEdge.y);
				transformedEdges.minEdge.z = glm::min(transformedEdges.minEdge.z, childEdges.minEdge.z);

				transformedEdges.maxEdge.x = glm::max(childEdges.maxEdge.x, transformedEdges.maxEdge.x);
				transformedEdges.maxEdge.y = glm::max(childEdges.maxEdge.y, transformedEdges.maxEdge.y);
				transformedEdges.maxEdge.z = glm::max(childEdges.maxEdge.z, transformedEdges.maxEdge.z);
			}

			collisionVertices = generateCBVertices(transformedEdges);
		}
		//else collisionBoxVertices = generateCBVertices(getTransformedEdges(vertices));
		else collisionVertices = transformVertices(vertices);

		transform->setTransformedSinceCBUpdate(false);
	}

	return collisionVertices;
}

vector<vec3> Entity::getTransformedVertices(vector<vec3> vertices)
{
	if (vertices.size() == 0)
	{
		cout << "Can not get transformed vertices: vertex vector is empty" << endl;
		return vector<vec3>();
	}

	CollisionBoxEdges edges;
	edges.minEdge.x = vertices[0].x;
	edges.minEdge.y = vertices[0].y;
	edges.minEdge.z = vertices[0].z;

	edges.maxEdge.x = vertices[0].x;
	edges.maxEdge.y = vertices[0].y;
	edges.maxEdge.z = vertices[0].z;

	for (int j = 0; j < vertices.size(); j++)
	{
		edges.minEdge.x = glm::min(edges.minEdge.x, vertices[j].x);
		edges.minEdge.y = glm::min(edges.minEdge.y, vertices[j].y);
		edges.minEdge.z = glm::min(edges.minEdge.z, vertices[j].z);

		edges.maxEdge.x = glm::max(vertices[j].x, edges.maxEdge.x);
		edges.maxEdge.y = glm::max(vertices[j].y, edges.maxEdge.y);
		edges.maxEdge.z = glm::max(vertices[j].z, edges.maxEdge.z);
	}
	vector<vec3> cbVertices = generateCBVertices(edges);

	//vector<vec3> transformedVertices;
	//for (int i = 0; i < cbVertices.size(); i++)
	//{
	//	vec3 vertex = vec3(transform->getGlobalModel() * vec4(cbVertices[i], 1.0f));
	//	vertex.x *= -1.0f;
	//	transformedVertices.push_back(vertex);
	//}
	//
	//return transformedVertices;

	return transformVertices(cbVertices);
}

CollisionBoxEdges Entity::getTransformedEdges(vector<vec3> vertices)
{
	CollisionBoxEdges edges;
	vec3 vertex = vec3(transform->getGlobalModel() * vec4(vertices[0], 1.0f));
	vertex.x *= -1.0f;

	edges.minEdge.x = vertex.x;
	edges.minEdge.y = vertex.y;
	edges.minEdge.z = vertex.z;

	edges.maxEdge.x = vertex.x;
	edges.maxEdge.y = vertex.y;
	edges.maxEdge.z = vertex.z;

	for (int j = 0; j < vertices.size(); j++)
	{
		vec3 vertex = vec3(transform->getGlobalModel() * vec4(vertices[j], 1.0f));
		vertex.x *= -1.0f;

		edges.minEdge.x = glm::min(edges.minEdge.x, vertex.x);
		edges.minEdge.y = glm::min(edges.minEdge.y, vertex.y);
		edges.minEdge.z = glm::min(edges.minEdge.z, vertex.z);

		edges.maxEdge.x = glm::max(vertex.x, edges.maxEdge.x);
		edges.maxEdge.y = glm::max(vertex.y, edges.maxEdge.y);
		edges.maxEdge.z = glm::max(vertex.z, edges.maxEdge.z);
	}

	return edges;
}

//vector<vec3> Entity::getCollisionBoxVertices()
//{
//	//if (transform->getTransformedSinceCBUpdate())
//	//{
//	//	if (children.size() > 0)
//	//	{
//	//		vector<vec3> transformedVertices = getTransformedVertices();
//	//		CollisionBoxEdges transformedEdges = generateCollisonBoxEdges(transformedVertices);
//	//
//	//		for (int i = 0; i < children.size(); i++)
//	//		{
//	//			vector<vec3> childVertices = dynamic_cast<Entity*>(children[i])->getCollisionBoxVertices();
//	//			CollisionBoxEdges childEdges = generateCollisonBoxEdges(childVertices);
//	//
//	//			transformedEdges.minEdge.x = glm::min(transformedEdges.minEdge.x, childEdges.minEdge.x);
//	//			transformedEdges.minEdge.y = glm::min(transformedEdges.minEdge.y, childEdges.minEdge.y);
//	//			transformedEdges.minEdge.z = glm::min(transformedEdges.minEdge.z, childEdges.minEdge.z);
//	//
//	//			transformedEdges.maxEdge.x = glm::max(childEdges.maxEdge.x, transformedEdges.maxEdge.x);
//	//			transformedEdges.maxEdge.y = glm::max(childEdges.maxEdge.y, transformedEdges.maxEdge.y);
//	//			transformedEdges.maxEdge.z = glm::max(childEdges.maxEdge.z, transformedEdges.maxEdge.z);
//	//		}
//	//
//	//		collisionBoxVertices = generateCollisonBoxVertices(transformedEdges);
//	//	}
//	//	else collisionBoxVertices = generateCollisonBoxVertices(getTransformedEdges());
//	//
//	//	transform->setTransformedSinceCBUpdate(false);
//	//}
//	//
//	//return collisionBoxVertices;
//}
#pragma endregion

#pragma region Rendering
void Entity::setRenderer(Renderer* _renderer) { renderer = _renderer; }

void Entity::setTextureManager(TextureManager * _textureManager) { textureManager = _textureManager; }

void Entity::setUniformValues()
{
	unsigned int uniformLocation;

	//Texture
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(shader), "spriteTextureActive");
	glUniform1i(uniformLocation, spriteTextureActive);

	//Color
	if (!spriteTextureActive)
	{
		uniformLocation = glGetUniformLocation(renderer->getShaderProgram(shader), "color");
		glUniform3f(uniformLocation, color.r, color.g, color.b);
	}

	//Material
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(shader), "material.diffuseTexturesActive");
	glUniform1i(uniformLocation, material.diffuseTexturesActive);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(shader), "material.specularTexturesActive");
	glUniform1i(uniformLocation, material.specularTexturesActive);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(shader), "material.diffuse");
	glUniform3f(uniformLocation, material.diffuse.r, material.diffuse.g, material.diffuse.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(shader), "material.specular");
	glUniform3f(uniformLocation, material.specular.r, material.specular.g, material.specular.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(shader), "material.shininess");
	glUniform1f(uniformLocation, material.shininess);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(shader), "material.alpha");
	glUniform1f(uniformLocation, material.alpha);
}

Renderer* Entity::getRenderer() { return renderer; }

Transform* Entity::getTransform() { return transform; }

void Entity::updateModels(mat4 otherModel)
{
	transform->updateGlobalModel(otherModel);

	for (int i = 0; i < children.size(); i++) children[i]->updateModels(otherModel);
}

void Entity::setShouldBeDrawn(bool _shouldBeDrawn)
{
	if (!renderizable) cout << "Can not set if entity should be drawn: entity is non-renderizable" << endl;
	else shouldBeDrawn = _shouldBeDrawn;
}
bool Entity::getShouldBeDrawn() { return shouldBeDrawn; }

void Entity::setColor(vec3 value) { color = value; }
vec3 Entity::getColor() { return color; }

void Entity::setMaterial(Material value) { material = value; }
Material Entity::getMaterial() { return material; }
#pragma endregion

#pragma region Parent
void Entity::setParent(Entity* _parent)
{
	if (parent == _parent) return;

	if (parent) parent->removeChild(this);

	parent = _parent;
	if (parent)
	{
		transform->setParent(parent->getTransform());

		vector<Entity*>::iterator reIterator;
		for (reIterator = renderizableEntities.begin(); reIterator < renderizableEntities.end(); reIterator++)
		{
			if (*reIterator == this)
			{
				renderizableEntities.erase(reIterator);
				break;
			}
		}
	}
	else
	{
		transform->setParent(NULL);
		renderizableEntities.push_back(this);
	}
}

Entity* Entity::getParent() { return parent; }
#pragma endregion

#pragma region Children
vector<Entity*> Entity::getChildren() { return children; }

void Entity::addChild(Entity* child)
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

void Entity::removeChild(Entity* child)
{
	vector<Entity*>::iterator childrenIterator;
	for (childrenIterator = children.begin(); childrenIterator < children.end(); childrenIterator++)
	{
		if (*childrenIterator == child)
		{
			children.erase(childrenIterator);
			transform->removeChild(child->getTransform());
			child->setParent(NULL);

			return;
		}
	}

	cout << "Child entity intended to be removed from parent was not found" << endl;
}
#pragma endregion

//vector<vec3> Entity::getCollisionVertices()
//{
//	cout << "Base Entity class can not generate collision box vertices" << endl;
//	return vector<vec3>();
//}

void Entity::draw()
{
	//if (!children.empty())
	//	for (int i = 0; i < children.size(); i++) children[i]->draw();
}