#include "Cube.h"

vec3 cubeColor = vec3(1.0f, 0.75f, 0.1f);

float Cube::vertices[] =
{
	//Position              //Color                                    //Normal               //UV       
	//-----------------
	-0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
							/*										*/
	-0.5f, -0.5f,  0.5f,    /*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,    /*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
							/*										*/
	-0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
							/*										*/
	 0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
							/*										*/
	-0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
							/*										*/
	-0.5f,  0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  1.0f,  0.0f,	 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	/*cubeColor.r, cubeColor.g, cubeColor.b,*/     0.0f,  1.0f,  0.0f,    0.0f, 1.0f
	//-----------------
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
	Entity::draw();

	renderer->setModel(renderer->getShaderProgram(ShaderType::Main), modelMatrix.model);
	renderer->setBufferData(CUBE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->drawTriangles(vertexAmount);
}