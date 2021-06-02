#include "Cube.h"

vec3 cubeColor = vec3(1.0f, 0.75f, 0.1f);

float Cube::vertices[] =
{
	//Position              //Normal               //UV       
	//-----------------
	-0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
							
	-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
							
	-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
							
	 0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
							
	-0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
							
	-0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,	   1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f
	//-----------------
};

unsigned int Cube::indices[] =
{
	0, 1, 2,
	3, 4, 5,
	6, 7, 8,
	9, 10, 11,
	12, 13, 14,
	15, 16, 17,
	18, 19, 20,
	21, 22, 23,
	24, 25, 26,
	27, 28, 29,
	30, 31, 32,
	33, 34, 35
};

Cube::Cube(Renderer* _renderer) : Entity(_renderer)
{
	renderer = _renderer;
	for (int i = 0; i < CUBE_VERTEX_COMPONENTS; i++) vertexBuffer[i] = vertices[i];
}

Cube::Cube(Renderer* _renderer, vec3 _color) : Entity(_renderer, _color)
{
	renderer = _renderer;
	for (int i = 0; i < CUBE_VERTEX_COMPONENTS; i++) vertexBuffer[i] = vertices[i];
}

Cube::Cube(Renderer* _renderer, Material _material) : Entity(_renderer, _material)
{
	renderer = _renderer;
	for (int i = 0; i < CUBE_VERTEX_COMPONENTS; i++) vertexBuffer[i] = vertices[i];
}

Cube::Cube(Renderer* _renderer, vec3 _color, Material _material) : Entity(_renderer, _color, _material)
{
	renderer = _renderer;
	for (int i = 0; i < CUBE_VERTEX_COMPONENTS; i++) vertexBuffer[i] = vertices[i];
}

Cube::~Cube() {}

void Cube::draw()
{
	setUniformValues();
	renderer->setModel(renderer->getShaderProgram(ShaderType::Main), modelMatrix.model);

	renderer->setVertexBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->setIndexBufferData(CUBE_INDICES, indices);
	renderer->drawElements(CUBE_INDICES);
}