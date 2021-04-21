#include "Light.h"

Light::Light(Renderer* _renderer) : Cube(_renderer) {}

Light::Light(Renderer* _renderer, vec3 _ambient, vec3 _diffuse, vec3 _specular) : Cube(_renderer)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
}

Light::~Light() {}

void Light::setAmbient(vec3 value) { ambient = value; }
vec3 Light::getAmbient() { return ambient; }

void Light::setDiffuse(vec3 value) { diffuse = value; }
vec3 Light::getDiffuse() { return diffuse; }

void Light::setSpecular(vec3 value) { specular = value; }
vec3 Light::getSpecular() { return specular; }

void Light::draw()
{
	Entity::draw();

	renderer->setModel(renderer->getShaderProgram(ShaderType::LightSource), modelMatrix.model);
	renderer->setBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->drawTriangles(vertexAmount);
}