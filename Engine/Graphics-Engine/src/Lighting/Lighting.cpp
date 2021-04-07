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

void Lighting::enableDirectionalLight(vec3 color, vec3 position)
{
	directionalLightActive = true;

	directionalLightColor = color;
	directionalLightPosition = position;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "directionalLightActive");
	glUniform1i(uniformLocation, directionalLightActive);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "directionalLightColor");
	glUniform3f(uniformLocation, directionalLightColor.r, directionalLightColor.g, directionalLightColor.b);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "directionalLightPosition");
	glUniform3f(uniformLocation, directionalLightPosition.x, directionalLightPosition.y, directionalLightPosition.z);
}

void Lighting::disableDirectionalLight()
{
	directionalLightActive = false;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "directionalLightActive");
	glUniform1i(uniformLocation, directionalLightActive);
}

void Lighting::setDirectionalLightActive(bool value) { directionalLightActive = value; }

bool Lighting::getDirectionalLightActive() { return directionalLightActive; }

void Lighting::setDirectionalLightPosition(vec3 value) { directionalLightPosition = value; }

vec3 Lighting::getDirectionalLightPosition() { return directionalLightPosition; }