#include "LightCube.h"

LightCube::LightCube(Renderer* _renderer) : Cube(_renderer)
{
	setScale(0.2f, 0.2f, 0.2f);
}

LightCube::~LightCube() {}

void LightCube::draw()
{
	renderer->setModel(renderer->getShaderProgram(ShaderType::LightSource), modelMatrix.model);

	renderer->setVertexBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->setIndexBufferData(CUBE_INDICES, indices);
	renderer->drawElements(CUBE_INDICES);
}