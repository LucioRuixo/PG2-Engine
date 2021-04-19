#include "Lighting.h"

Lighting::Lighting(Renderer* _renderer)
{
	renderer = _renderer;
}

Lighting::Lighting(Renderer* _renderer, Light _lightSource/*, float _ambientLightStrength*/)
{
	renderer = _renderer;

	//ambientLightStrength = _ambientLightStrength;
	lightSource = _lightSource;
}

Lighting::~Lighting() { if (lightSourceIcon) delete lightSourceIcon; }

#pragma region Light Source
void Lighting::enableLightSource(Light _lightSource)
{
	lightSourceActive = true;
	lightSource = _lightSource;

	//Active
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "lightSourceActive");
	glUniform1i(uniformLocation, lightSourceActive);

	//Position
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "light.position");
	glUniform3f(uniformLocation, lightSource.position.x, lightSource.position.y, lightSource.position.z);

	//Ambient
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "light.ambient");
	glUniform3f(uniformLocation, lightSource.ambient.r, lightSource.ambient.g, lightSource.ambient.b);

	//Diffuse
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "light.diffuse");
	glUniform3f(uniformLocation, lightSource.diffuse.r, lightSource.diffuse.g, lightSource.diffuse.b);

	//Specular
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "light.specular");
	glUniform3f(uniformLocation, lightSource.specular.r, lightSource.specular.g, lightSource.specular.b);

	if (!lightSourceIcon)
	{
		lightSourceIconPath = "../Graphics-Engine/res/Assets/Light Icon White.png";

		Material lightSourceMaterial; //TODO: hacer que las fuentes de luz tengan su propio shader
		lightSourceMaterial.ambient = vec3(1.0f);
		lightSourceMaterial.diffuse = vec3(0.0f);
		lightSourceMaterial.specular = vec3(0.0f);
		lightSourceIcon = new Sprite(renderer, vec3(1.0f), lightSourceMaterial);
		lightSourceIcon->setTexture(lightSourceIconPath, GL_RGBA);

		lightSourceIcon->setScale(0.25f, 0.25f, 0.0f);
	}
	lightSourceIcon->setPosition(lightSource.position.x, lightSource.position.y, lightSource.position.z);
}

void Lighting::disableLightSource()
{
	lightSourceActive = false;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "lightSourceActive");
	glUniform1i(uniformLocation, lightSourceActive);
}

void Lighting::setLightSourceActive(bool value) { lightSourceActive = value; }

bool Lighting::getLightSourceActive() { return lightSourceActive; }

void Lighting::setLightSourcePosition(vec3 value) { lightSource.position = value; }

vec3 Lighting::getLightSourcePosition() { return lightSource.position; }

Sprite* Lighting::getLightSourceIcon() { return lightSourceIcon; }
#pragma endregion

#pragma region Specular
//void Lighting::setSpecularStrength(float value)
//{
//	specularStrength = value;
//
//	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "specularStrength");
//	glUniform1f(uniformLocation, specularStrength);
//}
//
//float Lighting::getSpecularStrength() { return specularStrength; }
#pragma endregion