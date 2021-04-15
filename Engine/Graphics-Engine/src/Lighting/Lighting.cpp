#include "Lighting.h"

Lighting::Lighting(Renderer* _renderer)
{
	renderer = _renderer;
}

Lighting::Lighting(Renderer* _renderer, vec3 _ambientLightColor, float _ambientLightStrength)
{
	renderer = _renderer;

	ambientLightStrength = _ambientLightStrength;
	ambientLightColor = _ambientLightColor;
}

Lighting::~Lighting() { if (lightSourceIcon) delete lightSourceIcon; }

//Ambient light
//-----------------

void Lighting::setAmbientLightStrength(float value)
{
	ambientLightStrength = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "ambientLightStrength");
	glUniform1f(uniformLocation, ambientLightStrength);
}

void Lighting::setAmbientLightColor(vec3 value)
{
	ambientLightColor = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "ambientLightColor");
	glUniform3f(uniformLocation, ambientLightColor.r, ambientLightColor.g, ambientLightColor.b);
}

float Lighting::getAmbientLightStrength() { return ambientLightStrength; }

vec3 Lighting::getAmbientLightColor() { return ambientLightColor; }

//Light source
//-----------------

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

	if (!lightSourceIcon)
	{
		lightSourceIconPath = "../Graphics-Engine/res/Assets/Light Icon White.png";
		lightSourceIcon = new Sprite(renderer);
		lightSourceIcon->setTexture(lightSourceIconPath, GL_RGBA);
		lightSourceIcon->setScale(0.25f, 0.25f, 0.0f);
	}
	lightSourceIcon->setPosition(lightSourcePosition);
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

Sprite* Lighting::getLightSourceIcon() { return lightSourceIcon; }

//Specular
//-----------------

void Lighting::setSpecularStrength(float value)
{
	specularStrength = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "specularStrength");
	glUniform1f(uniformLocation, specularStrength);

	std::cout << "specularStrength: " << specularStrength << std::endl;
}

float Lighting::getSpecularStrength() { return specularStrength; }