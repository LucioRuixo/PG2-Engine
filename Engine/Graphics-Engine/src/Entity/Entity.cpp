#include "Entity.h"

Renderer* Entity::renderer = NULL;
TextureManager* Entity::textureManager = NULL;

Entity::Entity()
{
	transform = new Transform();
}

Entity::Entity(vector<Entity*> _children)
{
	transform = new Transform();

	for (int i = 0; i < _children.size(); i++) addChild(_children[i]);
}

Entity::Entity(vec3 _color)
{
	transform = new Transform();

	setColor(_color);
}

Entity::Entity(Material _material)
{
	transform = new Transform();

	setMaterial(_material);
}

Entity::Entity(vec3 _color, Material _material)
{
	transform = new Transform();

	setColor(_color);
	setMaterial(_material);
}

Entity::~Entity() { if (transform) delete transform; }

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
}

Renderer* Entity::getRenderer() { return renderer; }

Transform* Entity::getTransform() { return transform; }

void Entity::updateModels(mat4 otherModel)
{
	transform->updateGlobalModel(otherModel);

	for (int i = 0; i < children.size(); i++) children[i]->updateModels(otherModel);
}

void Entity::setColor(vec3 value) { color = value; }
vec3 Entity::getColor() { return color; }

void Entity::setMaterial(Material value) { material = value; }
Material Entity::getMaterial() { return material; }
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

#pragma region Parent
void Entity::setParent(Entity* _parent)
{
	if (parent == _parent) return;

	if (parent) parent->removeChild(this);

	parent = _parent;
	if (parent) transform->setParent(parent->getTransform());
	else transform->setParent(NULL);
}

Entity* Entity::getParent() { return parent; }
#pragma endregion

void Entity::draw()
{
	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->draw();
}