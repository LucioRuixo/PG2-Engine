#include "PointLight.h"

PointLight::PointLight(int _number, Renderer* _renderer) : Light(_renderer)
{
	lightCube = new LightCube();

	index = _number;
	setPosition(vec3(0.0f));
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setTerms(1.0f, 0.045f, 0.0075f);
	setOn(true);
}

PointLight::PointLight(int _number, Renderer* _renderer, vec3 _position) : Light(_renderer)
{
	lightCube = new LightCube();

	index = _number;
	setPosition(_position);
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setTerms(1.0f, 0.045f, 0.0075f);
	setOn(true);
}

PointLight::~PointLight() { if (lightCube) delete lightCube; }

void PointLight::setPosition(vec3 _position)
{
	position = _position;
	lightCube->setPosition(position.x, position.y, position.z);

	sprintf_s(characterBuffer, "pointLights[%i].position", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform3f(uniformLocation, position.x, position.y, position.z);
}
vec3 PointLight::getPosition() { return position; }

void PointLight::setDirection(vec3 _direction)
{
	std::cout << "Can not set direction in point light" << std::endl;
}
vec3 PointLight::getDirection()
{
	std::cout << "Can not get direction from point light, returning vec3(0.0f)" << std::endl;
	return vec3(0.0f);
}

void PointLight::setTerms(float _constant, float _linear, float _quadratic)
{
	setConstant(_constant);
	setLinear(_linear);
	setQuadratic(_quadratic);
}

void PointLight::setLightingComponents(vec3 _diffuse, vec3 _specular)
{
	setDiffuse(_diffuse);
	setSpecular(_specular);
}

void PointLight::setDiffuse(vec3 _diffuse)
{
	diffuse = _diffuse;

	sprintf_s(characterBuffer, "pointLights[%i].diffuse", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform3f(uniformLocation, diffuse.r, diffuse.g, diffuse.b);
}

void PointLight::setSpecular(vec3 _specular)
{
	specular = _specular;

	sprintf_s(characterBuffer, "pointLights[%i].specular", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform3f(uniformLocation, specular.r, specular.g, specular.b);
}

void PointLight::setConstant(float _constant)
{
	constant = _constant;

	sprintf_s(characterBuffer, "pointLights[%i].constant", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform1f(uniformLocation, constant);
}
float PointLight::getConstant() { return constant; }

void PointLight::setLinear(float _linear)
{
	linear = _linear;

	sprintf_s(characterBuffer, "pointLights[%i].linear", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform1f(uniformLocation, linear);
}
float PointLight::getLinear() { return linear; }

void PointLight::setQuadratic(float _quadratic)
{
	quadratic = _quadratic;

	sprintf_s(characterBuffer, "pointLights[%i].quadratic", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform1f(uniformLocation, quadratic);
}
float PointLight::getQuadratic() { return quadratic; }

void PointLight::setOn(bool _on)
{
	on = _on;

	sprintf_s(characterBuffer, "pointLights[%i].on", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), characterBuffer);
	glUniform1i(uniformLocation, on);
}

void PointLight::draw() { if (on && lightCube) lightCube->draw(); }