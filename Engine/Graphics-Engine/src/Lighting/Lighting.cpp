#include "Lighting.h"

Lighting::Lighting(Renderer* _renderer)
{
	renderer = _renderer;

	directionalLight = NULL;
	for (int i = 0; i < MAX_POINT_LIGHT_AMOUNT; i++) pointLights[i] = NULL;
	for (int i = 0; i < MAX_SPOTLIGHT_AMOUNT; i++) spotlights[i] = NULL;
}

Lighting::~Lighting()
{
	if (directionalLight) delete directionalLight;
	for (int i = 0; i < MAX_POINT_LIGHT_AMOUNT; i++) if (pointLights[i]) delete pointLights[i];
	for (int i = 0; i < MAX_SPOTLIGHT_AMOUNT; i++) if (spotlights[i]) delete spotlights[i];
}

void Lighting::initializeShaderValues()
{
	setAmbient(vec3(0.1f, 0.1f, 0.1f));

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.null");
	glUniform1i(uniformLocation, 1);

	char buffer[64];

	for (int i = 0; i < MAX_POINT_LIGHT_AMOUNT; i++)
	{
		sprintf_s(buffer, "pointLights[%i].null", i);
		uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
		glUniform1i(uniformLocation, 1);
	}


	for (int i = 0; i < MAX_SPOTLIGHT_AMOUNT; i++)
	{
		sprintf_s(buffer, "spotlights[%i].null", i);
		uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
		glUniform1i(uniformLocation, 1);
	}
}

void Lighting::setAmbient(vec3 _ambient)
{
	ambient = _ambient;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "lightingAmbient");
	glUniform3f(uniformLocation, ambient.r, ambient.g, ambient.b);
}
vec3 Lighting::getAmbient() { return ambient; }

void Lighting::addDirectionalLight(vec3 direction)
{
	if (directionalLight) delete directionalLight;

	directionalLight = new DirectionalLight(renderer, direction);

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.null");
	glUniform1i(uniformLocation, 0);
}

DirectionalLight* Lighting::getDirectionalLight() { return directionalLight; }

void Lighting::removeDirectionalLight()
{
	if (directionalLight)
	{
		delete directionalLight;
		directionalLight = NULL;
	}

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.null");
	glUniform1i(uniformLocation, 1);
}

void Lighting::addPointLight(int number, vec3 position)
{
	if (number < 0 || number >= MAX_POINT_LIGHT_AMOUNT)
	{
		std::cout << "Point light number " << number << " is out of range" << std::endl;
		return;
	}

	if (pointLights[number]) delete pointLights[number];
	pointLights[number] = new PointLight(number, renderer, position);

	char buffer[64];
	sprintf_s(buffer, "pointLights[%i].null", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1i(uniformLocation, 0);
}

PointLight* Lighting::getPointLight(int number)
{
	if (number < 0 || number >= MAX_POINT_LIGHT_AMOUNT)
	{
		std::cout << "Point light number " << number << " is out of range, returning null" << std::endl;
		return NULL;
	}

	return pointLights[number];
}

void Lighting::removePointLight(int number)
{
	if (number < 0 || number >= MAX_POINT_LIGHT_AMOUNT)
	{
		std::cout << "Point light number " << number << " is out of range" << std::endl;
		return;
	}

	if (pointLights[number])
	{
		delete pointLights[number];
		pointLights[number] = NULL;
	}

	char buffer[64];
	sprintf_s(buffer, "pointLights[%i].null", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1i(uniformLocation, 1);
}

void Lighting::addSpotlight(int number, vec3 position, vec3 direction)
{
	if (number < 0 || number >= MAX_SPOTLIGHT_AMOUNT)
	{
		std::cout << "Spotlight number " << number << " is out of range" << std::endl;
		return;
	}

	if (spotlights[number]) delete spotlights[number];
	spotlights[number] = new Spotlight(number, renderer, position, direction);

	char buffer[64];
	sprintf_s(buffer, "spotlights[%i].null", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1i(uniformLocation, 0);
}

Spotlight* Lighting::getSpotlight(int number)
{
	if (number < 0 || number >= MAX_SPOTLIGHT_AMOUNT)
	{
		std::cout << "Spotlight number " << number << " is out of range, returning null" << std::endl;
		return NULL;
	}

	return spotlights[number];
}

void Lighting::removeSpotlight(int number)
{
	if (number < 0 || number >= MAX_SPOTLIGHT_AMOUNT)
	{
		std::cout << "Spotlight number " << number << " is out of range" << std::endl;
		return;
	}

	if (spotlights[number])
	{
		delete spotlights[number];
		spotlights[number] = NULL;
	}

	char buffer[64];
	sprintf_s(buffer, "spotlights[%i].null", number);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1i(uniformLocation, 1);
}