#include "Lighting.h"

Lighting::Lighting(Renderer* _renderer)
{
	renderer = _renderer;

	ambientLightStrenth = 0.1f;
	ambientLightColor = vec3(1.0f, 1.0f, 1.0f);
}

Lighting::Lighting(Renderer* _renderer, vec3 _ambientLightColor, float _ambientLightStrenth)
{
	renderer = _renderer;

	ambientLightStrenth = _ambientLightStrenth;
	ambientLightColor = _ambientLightColor;
}

Lighting::~Lighting() {}

void Lighting::setAmbientLightStrenth(float value)
{
	ambientLightStrenth = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "ambientLightStrenth");
	glUniform1f(uniformLocation, ambientLightStrenth);
}

void Lighting::setAmbientLightColor(vec3 value)
{
	ambientLightColor = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "ambientLightColor");
	glUniform3f(uniformLocation, ambientLightColor.r, ambientLightColor.g, ambientLightColor.b);
}

float Lighting::getAmbientLightStrenth() { return ambientLightStrenth; }

vec3 Lighting::getAmbientLightColor() { return ambientLightColor; }

void Lighting::enableLightSource(vec3 color, vec3 position)
{
	lightSourceActive = true;

	lightSourceColor = color;
	lightSourcePosition = position;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "lightSourceActive");
	glUniform1i(uniformLocation, lightSourceActive);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "lightSourceColor");
	glUniform3f(uniformLocation, lightSourceColor.r, lightSourceColor.g, lightSourceColor.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "lightSourcePosition");
	glUniform3f(uniformLocation, lightSourcePosition.x, lightSourcePosition.y, lightSourcePosition.z);
}

void Lighting::disableLightSource()
{
	lightSourceActive = false;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "lightSourceActive");
	glUniform1i(uniformLocation, lightSourceActive);
}

void Lighting::setLightSourceActive(bool value) { lightSourceActive = value; }

bool Lighting::getLightSourceActive() { return lightSourceActive; }

void Lighting::setLightSourcePosition(vec3 value) { lightSourcePosition = value; }

vec3 Lighting::getLightSourcePosition() { return lightSourcePosition; }