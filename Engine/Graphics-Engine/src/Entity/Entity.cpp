#include "Entity.h"

Renderer* Entity::renderer = NULL;
TextureManager* Entity::textureManager = NULL;

Entity::Entity()
{
	transform = new Transform();
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

void Entity::setColor(vec3 value) { color = value; }
vec3 Entity::getColor() { return color; }

void Entity::setMaterial(Material value) { material = value; }
Material Entity::getMaterial() { return material; }

void Entity::draw()
{
	if (transform->getChildCount() > 0)
		for (int i = 0; i < transform->getChildCount(); i++) transform->getChildren()[i]->draw();
}