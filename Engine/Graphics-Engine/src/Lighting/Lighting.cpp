#include "Lighting.h"

Lighting::Lighting(Renderer* _renderer)
{
	renderer = _renderer;
}

Lighting::~Lighting() { if (lightSource) delete lightSource; }

#pragma region Light Source
void Lighting::enableLightSource(vec3 _position)
{
	enableLightSource(_position, vec3(0.1f), vec3(1.0f), vec3(1.0f));
}

void Lighting::enableLightSource(vec3 _position, vec3 _ambient, vec3 _diffuse, vec3 _specular)
{
	lightSourceActive = true;
	lightSource = new Light(renderer, _ambient, _diffuse, _specular);
	lightSource->setPosition(_position.x, _position.y, _position.z);
	lightSource->setScale(0.2f, 0.2f, 0.2f);

	//Active
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "lightSourceActive");
	glUniform1i(uniformLocation, lightSourceActive);

	//Position
	vec3 position = lightSource->transform->getPosition();
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.position");
	glUniform3f(uniformLocation, position.x, position.y, position.z);

	//Ambient
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.ambient");
	glUniform3f(uniformLocation, lightSource->getAmbient().r, lightSource->getAmbient().g, lightSource->getAmbient().b);

	//Diffuse
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.diffuse");
	glUniform3f(uniformLocation, lightSource->getDiffuse().r, lightSource->getDiffuse().g, lightSource->getDiffuse().b);

	//Specular
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.specular");
	glUniform3f(uniformLocation, lightSource->getSpecular().r, lightSource->getSpecular().g, lightSource->getSpecular().b);
}

Light* Lighting::getLightSource() { return lightSource; }

void Lighting::disableLightSource()
{
	lightSourceActive = false;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "lightSourceActive");
	glUniform1i(uniformLocation, lightSourceActive);
}

bool Lighting::getLightSourceActive() { return lightSourceActive; }

void Lighting::setLightSourcePosition(vec3 value) { lightSource->setPosition(value.x, value.y, value.y); }

vec3 Lighting::getLightSourcePosition() { return lightSource->transform->getPosition(); }
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