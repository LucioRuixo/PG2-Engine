#include "Cube.h"

float Cube::vertices[] =
{
	//Position              //Color              //Normal                //UV       
	//--------------
	-0.5f, -0.5f, -0.5f,  	1.0f, 0.0f, 0.0f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 0.0f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	0.0f, 0.0f, 1.0f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  	0.0f, 0.0f, 1.0f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	1.0f, 0.0f, 0.0f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	0.0f, 1.0f, 0.0f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	0.0f, 0.0f, 1.0f,     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 0.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  	0.0f, 0.0f, 1.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	0.0f, 0.0f, 1.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 0.0f,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	0.0f, 0.0f, 1.0f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  	0.0f, 0.0f, 1.0f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  	1.0f, 0.0f, 0.0f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 0.0f,     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 1.0f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 1.0f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	1.0f, 0.0f, 0.0f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  	1.0f, 0.0f, 0.0f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 0.0f,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	0.0f, 0.0f, 1.0f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	0.0f, 0.0f, 1.0f,     0.0f,  1.0f,  0.0f,	 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	1.0f, 0.0f, 0.0f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f
};																		 

Cube::Cube(Renderer* _renderer) : Entity(_renderer)
{
	renderer = _renderer;

	for (int i = 0; i < CUBE_VERTEX_COMPONENTS; i++) vertexBuffer[i] = vertices[i];
}

Cube::~Cube() {}

void Cube::draw()
{
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "textureActive");
	glUniform1i(uniformLocation, 0);

	renderer->setBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->setModel(renderer->getShaderProgram(), internalData.model);
	renderer->drawTriangles(vertexAmount);
}