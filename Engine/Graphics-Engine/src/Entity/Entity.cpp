#include "Entity.h"

Entity::Entity(Renderer *_renderer)
{
	renderer = _renderer;
	transform = new Transform();

	modelMatrix.model = mat4(1.0f);
	modelMatrix.rotationX = mat4(1.0f);
	modelMatrix.rotationY = mat4(1.0f);
	modelMatrix.rotationZ = mat4(1.0f);
	modelMatrix.scale = mat4(1.0f);
	modelMatrix.translation = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotationX(0.0f);
	setRotationY(0.0f);
	setRotationZ(0.0f);
	setScale(1.0f, 1.0f, 1.0f);
}

Entity::Entity(Renderer *_renderer, vec3 _color)
{
	renderer = _renderer;
	transform = new Transform();

	modelMatrix.model = mat4(1.0f);
	modelMatrix.rotationX = mat4(1.0f);
	modelMatrix.rotationY = mat4(1.0f);
	modelMatrix.rotationZ = mat4(1.0f);
	modelMatrix.scale = mat4(1.0f);
	modelMatrix.translation = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotationX(0.0f);
	setRotationY(0.0f);
	setRotationZ(0.0f);
	setScale(1.0f, 1.0f, 1.0f);

	setColor(_color);
}

Entity::Entity(Renderer* _renderer, Material _material)
{
	renderer = _renderer;
	transform = new Transform();

	modelMatrix.model = mat4(1.0f);
	modelMatrix.rotationX = mat4(1.0f);
	modelMatrix.rotationY = mat4(1.0f);
	modelMatrix.rotationZ = mat4(1.0f);
	modelMatrix.scale = mat4(1.0f);
	modelMatrix.translation = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotationX(0.0f);
	setRotationY(0.0f);
	setRotationZ(0.0f);
	setScale(1.0f, 1.0f, 1.0f);

	setMaterial(_material);
}

Entity::Entity(Renderer* _renderer, vec3 _color, Material _material)
{
	renderer = _renderer;
	transform = new Transform();

	modelMatrix.model = mat4(1.0f);
	modelMatrix.rotationX = mat4(1.0f);
	modelMatrix.rotationY = mat4(1.0f);
	modelMatrix.rotationZ = mat4(1.0f);
	modelMatrix.scale = mat4(1.0f);
	modelMatrix.translation = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotationX(0.0f);
	setRotationY(0.0f);
	setRotationZ(0.0f);
	setScale(1.0f, 1.0f, 1.0f);

	setColor(_color);
	setMaterial(_material);
}

Entity::~Entity() { if (transform) delete transform; }

void Entity::updateModelMatrix()
{
	modelMatrix.model = modelMatrix.translation *
						modelMatrix.rotationX * modelMatrix.rotationY * modelMatrix.rotationZ *
						modelMatrix.scale;
}

Renderer* Entity::getRenderer() { return renderer; }

mat4 Entity::getModel() { return modelMatrix.model; }

void Entity::setPosition(float x, float y, float z)
{
	transform->setPosition(x, y, z);

	modelMatrix.translation = glm::translate(mat4(1.0f), transform->getPosition());
	updateModelMatrix();
}

void Entity::translate(float x, float y, float z)
{
	vec3 position = transform->getPosition();
	setPosition(position.x + x, position.y + y, position.z + z);
}

void Entity::setRotationX(float x)
{
	transform->setRotation(x, transform->getRotation().y, transform->getRotation().z);
	vec3 axis = vec3(1.0f, 0.0f, 0.0f);

	modelMatrix.rotationX = rotate(mat4(1.0f), x, axis);
	updateModelMatrix();
}

void Entity::setRotationY(float y)
{
	transform->setRotation(transform->getRotation().x, y, transform->getRotation().z);
	vec3 axis = vec3(0.0f, 1.0f, 0.0f);

	modelMatrix.rotationY = rotate(mat4(1.0f), y, axis);
	updateModelMatrix();
}

void Entity::setRotationZ(float z)
{
	transform->setRotation(transform->getRotation().x, transform->getRotation().y, z);
	vec3 axis = vec3(0.0f, 0.0f, 1.0f);

	modelMatrix.rotationZ = rotate(mat4(1.0f), z, axis);
	updateModelMatrix();
}

void Entity::setColor(vec3 value) { color = value; }
vec3 Entity::getColor() { return color; }

void Entity::setMaterial(Material value) { material = value; }
Material Entity::getMaterial() { return material; }

void Entity::setScale(float x, float y, float z)
{
	transform->setScale(x, y, z);

	modelMatrix.scale = scale(mat4(1.0f), transform->getScale());
	updateModelMatrix();
}

void Entity::draw()
{
	int uniformLocation;

	//Color
	if (!textureActive)
	{
		uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "color");
		glUniform3f(uniformLocation, color.r, color.g, color.b);
	}

	//Material
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "material.ambient");
	glUniform3f(uniformLocation, material.ambient.r, material.ambient.g, material.ambient.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "material.diffuse");
	glUniform3f(uniformLocation, material.diffuse.r, material.diffuse.g, material.diffuse.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "material.specular");
	glUniform3f(uniformLocation, material.specular.r, material.specular.g, material.specular.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "material.shininess");
	glUniform1f(uniformLocation, material.shininess);

	//Texture
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "textureActive");
	glUniform1i(uniformLocation, textureActive);
}