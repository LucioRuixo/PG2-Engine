#include "PointLight.h"

PointLight::PointLight(int _number, Renderer* _renderer) : Light(_renderer)
{
	lightCube = new LightCube();

	number = _number;
	setPosition(vec3(0.0f));
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setTerms(1.0f, 0.045f, 0.0075f);
}

PointLight::PointLight(int _number, Renderer* _renderer, vec3 _position) : Light(_renderer)
{
	lightCube = new LightCube();

	number = _number;
	setPosition(_position);
	setLightingComponents(vec3(1.0f), vec3(1.0f));
	setTerms(1.0f, 0.045f, 0.0075f);
}

PointLight::~PointLight() { if (lightCube) delete lightCube; }

void PointLight::setPosition(vec3 _position)
{
	position = _position;
	lightCube->setPosition(position.x, position.y, position.z);

	sprintf_s(buffer, "pointLights[%i].position", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
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

	sprintf_s(buffer, "pointLights[%i].diffuse", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform3f(uniformLocation, diffuse.r, diffuse.g, diffuse.b);
}

void PointLight::setSpecular(vec3 _specular)
{
	specular = _specular;

	sprintf_s(buffer, "pointLights[%i].specular", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform3f(uniformLocation, specular.r, specular.g, specular.b);
}

void PointLight::setConstant(float _constant)
{
	constant = _constant;

	sprintf_s(buffer, "pointLights[%i].constant", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1f(uniformLocation, constant);
}
float PointLight::getConstant() { return constant; }

void PointLight::setLinear(float _linear)
{
	linear = _linear;

	sprintf_s(buffer, "pointLights[%i].linear", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1f(uniformLocation, linear);
}
float PointLight::getLinear() { return linear; }

void PointLight::setQuadratic(float _quadratic)
{
	quadratic = _quadratic;

	sprintf_s(buffer, "pointLights[%i].quadratic", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1f(uniformLocation, quadratic);
}
float PointLight::getQuadratic() { return quadratic; }

void PointLight::draw() { if (lightCube) lightCube->draw(); }