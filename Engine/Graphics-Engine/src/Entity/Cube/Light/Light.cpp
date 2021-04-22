#include "Light.h"

Light::Light(Renderer* _renderer, LightType _type) : Cube(_renderer)
{
	type = _type;

	setPosition(0.0f, 2.0f, 0.0f);
	setLightingComponents(vec3(0.1f), vec3(1.0f), vec3(1.0f));
	setDirection(normalize(vec3(0.0f, -1.0f, -1.0f)));
	setPointLightTerms(1.0f, 0.09f, 0.032f);
	setInnerCutOff(17.5f);
	setOuterCutOff(22.5f);
}

Light::~Light() {}

void Light::setPosition(float x, float y, float z)
{
	Entity::setPosition(x, y, z);

	vec3 position = transform->getPosition();
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.position");
	glUniform3f(uniformLocation, position.x, position.y, position.z);
}

void Light::translate(float x, float y, float z)
{
	vec3 position = transform->getPosition();
	setPosition(position.x + x, position.y + y, position.z + z);
}

void Light::setDirection(vec3 _direction)
{
	direction = normalize(_direction);

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.direction");
	glUniform3f(uniformLocation, direction.x, direction.y, direction.z);
}
vec3 Light::getDirection() { return direction; }

void Light::setType(LightType _type)
{
	type = _type;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.type");
	glUniform1i(uniformLocation, type);
}
LightType Light::getType() { return type; }

#pragma region Lighting Components
void Light::setLightingComponents(vec3 _ambient, vec3 _diffuse, vec3 _specular)
{
	setAmbient(_ambient);
	setDiffuse(_diffuse);
	setSpecular(_specular);
}

void Light::setAmbient(vec3 _ambient)
{ 
	ambient = _ambient;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.ambient");
	glUniform3f(uniformLocation, ambient.r, ambient.g, ambient.b);
}
vec3 Light::getAmbient() { return ambient; }

void Light::setDiffuse(vec3 _diffuse)
{ 
	diffuse = _diffuse;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.diffuse");
	glUniform3f(uniformLocation, diffuse.r, diffuse.g, diffuse.b);
}
vec3 Light::getDiffuse() { return diffuse; }

void Light::setSpecular(vec3 _specular)
{ 
	specular = _specular;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.specular");
	glUniform3f(uniformLocation, specular.r, specular.g, specular.b);
}
vec3 Light::getSpecular() { return specular; }
#pragma endregion

#pragma region Point Light
void Light::setPointLightTerms(float _constant, float _linear, float _quadratic)
{
	setConstant(_constant);
	setLinear(_linear);
	setQuadratic(_quadratic);
}

void Light::setConstant(float _constant)
{
	constant = _constant;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.constant");
	glUniform1f(uniformLocation, constant);
}
float Light::getConstant() { return constant; }

void Light::setLinear(float _linear)
{
	linear = _linear;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light._linear");
	glUniform1f(uniformLocation, linear);
}
float Light::getLinear() { return linear; }

void Light::setQuadratic(float _quadratic)
{
	quadratic = _quadratic;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.quadratic");
	glUniform1f(uniformLocation, quadratic);
}
float Light::getQuadratic() { return quadratic; }
#pragma endregion

#pragma region Spot Light
void Light::setInnerCutOff(float _innerCutOff)
{
	innerCutOff = _innerCutOff;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.innerCutOff");
	glUniform1f(uniformLocation, cos(radians(innerCutOff)));
}
float Light::getInnerCutOff() { return innerCutOff; }

void Light::setOuterCutOff(float _outerCutOff)
{
	outerCutOff = _outerCutOff;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "light.outerCutOff");
	glUniform1f(uniformLocation, cos(radians(outerCutOff)));
}
float Light::getOuterCutOff() { return outerCutOff; }
#pragma endregion

void Light::draw()
{
	Entity::draw();

	renderer->setModel(renderer->getShaderProgram(ShaderType::LightSource), modelMatrix.model);
	renderer->setBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->drawTriangles(vertexAmount);
}