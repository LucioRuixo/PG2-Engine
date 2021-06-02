#include "Entity.h"

Entity::Entity(Renderer *_renderer)
{
	construct(_renderer);
}

Entity::Entity(Renderer *_renderer, vec3 _color)
{
	construct(_renderer);

	setColor(_color);
}

Entity::Entity(Renderer* _renderer, Material _material)
{
	construct(_renderer);

	setMaterial(_material);
}

Entity::Entity(Renderer* _renderer, vec3 _color, Material _material)
{
	construct(_renderer);

	setColor(_color);
	setMaterial(_material);
}

Entity::~Entity() { if (transform) delete transform; }

void Entity::construct(Renderer * _renderer)
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
	setRotation(0.0f, 0.0f, 0.0f);
	setScale(1.0f, 1.0f, 1.0f);
}

void Entity::updateModelMatrix()
{
	modelMatrix.model = modelMatrix.translation *
						modelMatrix.rotationX * modelMatrix.rotationY * modelMatrix.rotationZ *
						modelMatrix.scale;
}

void Entity::setUniformValues()
{
	int uniformLocation;

	//Texture
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "textureActive");
	glUniform1i(uniformLocation, textureActive);

	//Color
	if (!textureActive)
	{
		uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "color");
		glUniform3f(uniformLocation, color.r, color.g, color.b);
	}

	//Material
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.ambient");
	glUniform3f(uniformLocation, material.ambient.r, material.ambient.g, material.ambient.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuse");
	glUniform3f(uniformLocation, material.diffuse.r, material.diffuse.g, material.diffuse.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specular");
	glUniform3f(uniformLocation, material.specular.r, material.specular.g, material.specular.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.shininess");
	glUniform1f(uniformLocation, material.shininess);
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

void Entity::setRotation(float x, float y, float z)
{
	transform->setRotation(x, y, z);

	vec3 xAxis = vec3(1.0f, 0.0f, 0.0f);
	vec3 yAxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 zAxis = vec3(0.0f, 0.0f, 1.0f);

	modelMatrix.rotationX = rotate(mat4(1.0f), x, xAxis);
	modelMatrix.rotationY = rotate(mat4(1.0f), y, yAxis);
	modelMatrix.rotationZ = rotate(mat4(1.0f), z, zAxis);

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