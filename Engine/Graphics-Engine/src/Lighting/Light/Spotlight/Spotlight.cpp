#include "Spotlight.h"

Spotlight::Spotlight(int _number, Renderer* _renderer) : Light(_renderer)
{
	lightCube = new LightCube(_renderer);

	number = _number;
	setPosition(vec3(0.0f, 0.0f, 0.0f));
	setDirection(vec3(-1.0f, -1.0f, -1.0f));
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setInnerCutOff(17.5f);
	setOuterCutOff(22.5f);
}

Spotlight::Spotlight(int _number, Renderer* _renderer, vec3 _position, vec3 _direction) : Light(_renderer)
{
	lightCube = new LightCube(_renderer);

	number = _number;
	setPosition(_position);
	setDirection(_direction);
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setInnerCutOff(17.5f);
	setOuterCutOff(22.5f);
}

Spotlight::~Spotlight() { if (lightCube) delete lightCube; }

void Spotlight::setPosition(vec3 _position)
{
	position = _position;
	lightCube->setPosition(position.x, position.y, position.z);

	sprintf_s(buffer, "spotlights[%i].position", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform3f(uniformLocation, position.x, position.y, position.z);
}
vec3 Spotlight::getPosition() { return position; }

void Spotlight::setDirection(vec3 _direction)
{
	direction = normalize(_direction);

	sprintf_s(buffer, "spotlights[%i].direction", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform3f(uniformLocation, direction.x, direction.y, direction.z);
}
vec3 Spotlight::getDirection() { return direction; }

void Spotlight::setLightingComponents(vec3 _diffuse, vec3 _specular)
{
	setDiffuse(_diffuse);
	setSpecular(_specular);
}

void Spotlight::setDiffuse(vec3 _diffuse)
{
	diffuse = _diffuse;

	sprintf_s(buffer, "spotlights[%i].diffuse", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform3f(uniformLocation, diffuse.r, diffuse.g, diffuse.b);
}

void Spotlight::setSpecular(vec3 _specular)
{
	specular = _specular;

	sprintf_s(buffer, "spotlights[%i].specular", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform3f(uniformLocation, specular.r, specular.g, specular.b);
}

void Spotlight::setInnerCutOff(float _innerCutOff)
{
	innerCutOff = _innerCutOff;

	sprintf_s(buffer, "spotlights[%i].innerCutOff", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1f(uniformLocation, cos(radians(innerCutOff)));
}
float Spotlight::getInnerCutOff() { return innerCutOff; }

void Spotlight::setOuterCutOff(float _outerCutOff)
{
	outerCutOff = _outerCutOff;

	sprintf_s(buffer, "spotlights[%i].outerCutOff", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1f(uniformLocation, cos(radians(outerCutOff)));
}
float Spotlight::getOuterCutOff() { return outerCutOff; }

void Spotlight::draw() { if (lightCube) lightCube->draw(); }