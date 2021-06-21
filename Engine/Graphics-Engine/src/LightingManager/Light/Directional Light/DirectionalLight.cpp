#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Renderer* _renderer) : Light(_renderer)
{
	setDirection(vec3(-1.0f, -1.0f, -1.0f));
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setOn(true);
}

DirectionalLight::DirectionalLight(Renderer* _renderer, vec3 _direction) : Light(_renderer)
{
	setDirection(_direction);
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setOn(true);
}

DirectionalLight::~DirectionalLight() {}

void DirectionalLight::setPosition(vec3 _position)
{
	std::cout << "Can not set position in directional light" << std::endl;
}
vec3 DirectionalLight::getPosition()
{
	std::cout << "Can not get position from directional light, returning vec3(0.0f)" << std::endl;
	return vec3(0.0f);
}

void DirectionalLight::setDirection(vec3 _direction)
{
	direction = normalize(_direction);

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.direction");
	glUniform3f(uniformLocation, direction.x, direction.y, direction.z);
}
vec3 DirectionalLight::getDirection() { return direction; }

void DirectionalLight::setLightingComponents(vec3 _diffuse, vec3 _specular)
{
	setDiffuse(_diffuse);
	setSpecular(_specular);
}

void DirectionalLight::setDiffuse(vec3 _diffuse)
{
	diffuse = _diffuse;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.diffuse");
	glUniform3f(uniformLocation, diffuse.r, diffuse.g, diffuse.b);
}

void DirectionalLight::setSpecular(vec3 _specular)
{
	specular = _specular;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.specular");
	glUniform3f(uniformLocation, specular.r, specular.g, specular.b);
}

void DirectionalLight::setOn(bool _on)
{
	on = _on;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.on");
	glUniform1i(uniformLocation, on);
}

void DirectionalLight::draw() { std::cout << "can not draw directional light" << std::endl; }