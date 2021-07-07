#include "Spotlight.h"

Spotlight::Spotlight(int _number, Renderer* _renderer) : Light(_renderer)
{
	lightCube = new LightCube();

	index = _number;
	setPosition(vec3(0.0f, 0.0f, 0.0f));
	setDirection(vec3(-1.0f, -1.0f, -1.0f));
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setInnerCutOff(17.5f);
	setOuterCutOff(22.5f);
	setOn(true);
}

Spotlight::Spotlight(int _number, Renderer* _renderer, vec3 _position, vec3 _direction) : Light(_renderer)
{
	lightCube = new LightCube();

	index = _number;
	setPosition(_position);
	setDirection(_direction);
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setInnerCutOff(17.5f);
	setOuterCutOff(22.5f);
	setOn(true);
}

Spotlight::~Spotlight() { if (lightCube) delete lightCube; }

void Spotlight::setPosition(vec3 _position)
{
	position = _position;
	lightCube->getTransform()->setPosition(position.x, position.y, position.z);

	sprintf_s(characterBuffer, "spotlights[%i].position", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform3f(uniformLocation, position.x, position.y, position.z);
}
vec3 Spotlight::getPosition() { return position; }

void Spotlight::setDirection(vec3 _direction)
{
	direction = normalize(_direction);

	sprintf_s(characterBuffer, "spotlights[%i].direction", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
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

	sprintf_s(characterBuffer, "spotlights[%i].diffuse", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform3f(uniformLocation, diffuse.r, diffuse.g, diffuse.b);
}

void Spotlight::setSpecular(vec3 _specular)
{
	specular = _specular;

	sprintf_s(characterBuffer, "spotlights[%i].specular", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform3f(uniformLocation, specular.r, specular.g, specular.b);
}

void Spotlight::setInnerCutOff(float _innerCutOff)
{
	innerCutOff = _innerCutOff;

	sprintf_s(characterBuffer, "spotlights[%i].innerCutOff", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform1f(uniformLocation, cos(radians(innerCutOff)));
}
float Spotlight::getInnerCutOff() { return innerCutOff; }

void Spotlight::setOuterCutOff(float _outerCutOff)
{
	outerCutOff = _outerCutOff;

	sprintf_s(characterBuffer, "spotlights[%i].outerCutOff", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform1f(uniformLocation, cos(radians(outerCutOff)));
}
float Spotlight::getOuterCutOff() { return outerCutOff; }

void Spotlight::setOn(bool _on)
{
	on = _on;

	sprintf_s(characterBuffer, "spotlights[%i].on", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform1i(uniformLocation, on);
}

void Spotlight::draw() { if (on && lightCube) lightCube->draw(); }