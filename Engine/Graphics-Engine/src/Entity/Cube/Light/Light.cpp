#include "Light.h"

Light::Light(Renderer* _renderer, LightType _type) : Cube(_renderer)
{
	type = _type;

	setPosition(0.0f, 2.0f, 0.0f);
	setDirection(normalize(vec3(0.0f, -1.0f, -1.0f)));
	setLightingComponents(vec3(0.1f), vec3(1.0f), vec3(1.0f));
}

Light::~Light() {}

void Light::setPosition(float x, float y, float z)
{
	Entity::setPosition(x, y, z);

	vec3 position = transform->getPosition();
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.position");
	glUniform3f(uniformLocation, position.x, position.y, position.z);
}

void Light::translate(float x, float y, float z)
{
	vec3 position = transform->getPosition();
	setPosition(position.x + x, position.y + y, position.z + z);
}

void Light::setType(LightType value)
{
	type = value;
	std::cout << "value: " << value << std::endl;
	std::cout << "type: " << type << std::endl;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.type");
	glUniform1i(uniformLocation, type);
}
LightType Light::getType() { return type; }

void Light::setDirection(vec3 value)
{
	direction = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.direction");
	glUniform3f(uniformLocation, direction.x, direction.y, direction.z);
}
vec3 Light::getDirection() { return direction; }

void Light::setLightingComponents(vec3 _ambient, vec3 _diffuse, vec3 _specular)
{
	setAmbient(_ambient);
	setDiffuse(_diffuse);
	setSpecular(_specular);
}

void Light::setAmbient(vec3 value)
{ 
	ambient = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.ambient");
	glUniform3f(uniformLocation, ambient.r, ambient.g, ambient.b);
}
vec3 Light::getAmbient() { return ambient; }

void Light::setDiffuse(vec3 value)
{ 
	diffuse = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.diffuse");
	glUniform3f(uniformLocation, diffuse.r, diffuse.g, diffuse.b);
}
vec3 Light::getDiffuse() { return diffuse; }

void Light::setSpecular(vec3 value)
{ 
	specular = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.specular");
	glUniform3f(uniformLocation, specular.r, specular.g, specular.b);
}
vec3 Light::getSpecular() { return specular; }

void Light::draw()
{
	Entity::draw();

	renderer->setModel(renderer->getShaderProgram(ShaderType::LightSource), modelMatrix.model);
	renderer->setBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->drawTriangles(vertexAmount);
}