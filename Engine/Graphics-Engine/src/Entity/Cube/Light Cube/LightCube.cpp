#include "LightCube.h"

LightCube::LightCube() : Cube()
{
	shader = ShaderType::LightSource;
	transform->setScale(0.2f, 0.2f, 0.2f);
}

LightCube::~LightCube() {}

void LightCube::draw()
{
	renderer->setModel(renderer->getShaderProgram(ShaderType::LightSource), transform->getModel().model);
	renderer->drawElements(vao, vbo, ebo, CUBE_INDICES);
}