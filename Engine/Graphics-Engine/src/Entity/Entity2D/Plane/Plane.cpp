#include "Plane.h"

//T = top
//B = bottom
//L = left
//R = right
vec2 TL = vec2(-0.5f, 0.5f);
vec2 TR = vec2(0.5f, 0.5f);
vec2 BL = vec2(-0.5f, -0.5f);
vec2 BR = vec2(0.5f, -0.5f);
vec2 boundsMin = BL;
vec2 boundsMax = TR;

float Plane::vertices[] =
{
	//Position           //Color              //Normal             //UV       
	//--------------									      
	//With TBLR							      
	TL.x, TL.y, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
	TR.x, TR.y, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	BR.x, BR.y, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,

	BR.x, BR.y, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
	BL.x, BL.y, 0.0f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
	TL.x, TL.y, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f

	//Without TBLR
	//-0.5f,  0.5f, 0.0f,	   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
	// 0.5f,  0.5f, 0.0f,	   0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	// 0.5f, -0.5f, 0.0f,	   0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
	//					   					    
	// 0.5f, -0.5f, 0.0f,	   0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
	//-0.5f, -0.5f, 0.0f,	   1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
	//-0.5f,  0.5f, 0.0f,	   1.0f, 0.0f, 0.0f,    1.0f, 1.0f
	//--------------									      
};

/*
float indexedVertices[] =
{
	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f
};

unsigned int indices[] =
{
	0, 1, 3,   //1st triangle
	1, 2, 3    //2nd triangle
};
*/

Plane::Plane(Renderer* _renderer) : Entity2D(_renderer, boundsMin, boundsMax)
{
	renderer = _renderer;

	for (int i = 0; i < PLANE_VERTEX_COMPONENTS; i++) vertexBuffer[i] = vertices[i];
}

Plane::~Plane() {}

void Plane::draw()
{
	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "textureActive");
	glUniform1i(uniformLocation, 0);

	renderer->setBufferData(PLANE_VERTEX_COMPONENTS, vertexBuffer);
	renderer->setModel(renderer->getShaderProgram(), matrixData.mainMatrix);
	renderer->drawTriangles(vertexAmount);
}