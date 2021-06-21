#include "LightingManager.h"

LightingManager::LightingManager(Renderer* _renderer)
{
	renderer = _renderer;

	directionalLight = NULL;
	for (int i = 0; i < MAX_POINT_LIGHT_AMOUNT; i++) pointLights[i] = NULL;
	for (int i = 0; i < MAX_SPOTLIGHT_AMOUNT; i++) spotlights[i] = NULL;
}

LightingManager::~LightingManager()
{
	if (directionalLight) delete directionalLight;
	for (int i = 0; i < MAX_POINT_LIGHT_AMOUNT; i++) if (pointLights[i]) delete pointLights[i];
	for (int i = 0; i < MAX_SPOTLIGHT_AMOUNT; i++) if (spotlights[i]) delete spotlights[i];
}

void LightingManager::initializeShaderValues()
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

void LightingManager::setAmbient(vec3 _ambient)
{
	ambient = _ambient;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "lightingAmbient");
	glUniform3f(uniformLocation, ambient.r, ambient.g, ambient.b);
}
vec3 LightingManager::getAmbient() { return ambient; }

void LightingManager::addDirectionalLight(vec3 direction)
{
	if (directionalLight) delete directionalLight;

	directionalLight = new DirectionalLight(renderer, direction);

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.null");
	glUniform1i(uniformLocation, 0);
}

DirectionalLight* LightingManager::getDirectionalLight() { return directionalLight; }

void LightingManager::removeDirectionalLight()
{
	if (directionalLight)
	{
		delete directionalLight;
		directionalLight = NULL;
	}

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "directionalLight.null");
	glUniform1i(uniformLocation, 1);
}

void LightingManager::addPointLight(int index, vec3 position)
{
	if (index < 0 || index >= MAX_POINT_LIGHT_AMOUNT)
	{
		std::cout << "Point light number " << index << " is out of range" << std::endl;
		return;
	}

	if (pointLights[index]) delete pointLights[index];
	pointLights[index] = new PointLight(index, renderer, position);

	char buffer[64];
	sprintf_s(buffer, "pointLights[%i].null", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1i(uniformLocation, 0);
}

PointLight* LightingManager::getPointLight(int index)
{
	if (index < 0 || index >= MAX_POINT_LIGHT_AMOUNT)
	{
		std::cout << "Point light number " << index << " is out of range, returning null" << std::endl;
		return NULL;
	}

	return pointLights[index];
}

void LightingManager::removePointLight(int index)
{
	if (index < 0 || index >= MAX_POINT_LIGHT_AMOUNT)
	{
		std::cout << "Point light number " << index << " is out of range" << std::endl;
		return;
	}

	if (pointLights[index])
	{
		delete pointLights[index];
		pointLights[index] = NULL;
	}

	char buffer[64];
	sprintf_s(buffer, "pointLights[%i].null", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1i(uniformLocation, 1);
}

void LightingManager::addSpotlight(int index, vec3 position, vec3 direction)
{
	if (index < 0 || index >= MAX_SPOTLIGHT_AMOUNT)
	{
		std::cout << "Spotlight number " << index << " is out of range" << std::endl;
		return;
	}

	if (spotlights[index]) delete spotlights[index];
	spotlights[index] = new Spotlight(index, renderer, position, direction);

	char buffer[64];
	sprintf_s(buffer, "spotlights[%i].null", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1i(uniformLocation, 0);
}

Spotlight* LightingManager::getSpotlight(int index)
{
	if (index < 0 || index >= MAX_SPOTLIGHT_AMOUNT)
	{
		std::cout << "Spotlight number " << index << " is out of range, returning null" << std::endl;
		return NULL;
	}

	return spotlights[index];
}

void LightingManager::removeSpotlight(int index)
{
	if (index < 0 || index >= MAX_SPOTLIGHT_AMOUNT)
	{
		std::cout << "Spotlight number " << index << " is out of range" << std::endl;
		return;
	}

	if (spotlights[index])
	{
		delete spotlights[index];
		spotlights[index] = NULL;
	}

	char buffer[64];
	sprintf_s(buffer, "spotlights[%i].null", index);
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), buffer);
	glUniform1i(uniformLocation, 1);
}