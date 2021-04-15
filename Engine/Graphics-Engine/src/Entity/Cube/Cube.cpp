#include "Cube.h"

vec3 cubeColor = vec3(1.0f, 0.75f, 0.1f);

float Cube::vertices[] =
{
	//Position              //Color                                    //Normal               //UV       
	//-----------------
	-0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
							
	-0.5f, -0.5f,  0.5f,    cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,    cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
							
	-0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
							
	 0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
							
	-0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
							
	-0.5f,  0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  1.0f,  0.0f,	 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	cubeColor.r, cubeColor.g, cubeColor.b,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f
	//-----------------
};																		 

Cube::Cube(Renderer* _renderer) : Entity(_renderer)
{
	renderer = _renderer;

	for (int i = 0; i < CUBE_VERTEX_COMPONENTS; i++) vertexBuffer[i] = vertices[i];

	vertices[4] = 69.0f;
}

Cube::~Cube() {}

void Cube::draw()
{
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "textureActive");
	glUniform1i(uniformLocation, 0);

	renderer->setBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->setModel(renderer->getShaderProgram(), modelMatrix.model);
	renderer->drawTriangles(vertexAmount);
}