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