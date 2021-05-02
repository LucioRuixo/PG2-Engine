#include "LightCube.h"

LightCube::LightCube(Renderer* _renderer) : Cube(_renderer)
{
	setScale(0.2f, 0.2f, 0.2f);
}

LightCube::~LightCube() {}

void LightCube::draw()
{
	renderer->setModel(renderer->getShaderProgram(ShaderType::LightSource), modelMatrix.model);
	renderer->setBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->drawTriangles(vertexAmount);
}