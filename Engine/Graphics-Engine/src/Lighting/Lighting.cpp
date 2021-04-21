#include "Lighting.h"

Lighting::Lighting(Renderer* _renderer)
{
	renderer = _renderer;

	lightSource = NULL;
}

Lighting::~Lighting() { if (lightSource) delete lightSource; }

void Lighting::createLightSource()
{
	if (lightSource) delete lightSource;

	lightSource = new Light(renderer, LightType::Directional);
	lightSource->setScale(0.2f, 0.2f, 0.2f);
}

Light* Lighting::getLightSource() { return lightSource; }

void Lighting::setLightSourceActive(bool value)
{
	lightSourceActive = value;

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "lightSourceActive");
	glUniform1i(uniformLocation, lightSourceActive);
}
bool Lighting::getLightSourceActive() { return lightSourceActive; }

void Lighting::setLightSourcePosition(vec3 value) { lightSource->setPosition(value.x, value.y, value.y); }
vec3 Lighting::getLightSourcePosition() { return lightSource->transform->getPosition(); }