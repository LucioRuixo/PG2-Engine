#include "Sprite.h"
using namespace glm;

float vertexBufferTriSprite[] = {
	-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.5f, 1.0f
}; 

unsigned int triIndicesSprite[] = {
	0, 1, 2
};

//T = top
//B = bottom
//L = left
//R = right
vec2 TL = vec2(-0.5f,  0.5f);
vec2 TR = vec2( 0.5f,  0.5f);
vec2 BL = vec2(-0.5f, -0.5f);
vec2 BR = vec2( 0.5f, -0.5f);
vec2 _boundsMin = BL;
vec2 _boundsMax = TR;

float vertexBufferQuadSprite[QUAD_VERTEX_BUFFER_SIZE] = {
	//TL.x, TL.y, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.5f,
	//TR.x, TR.y, 0.0f,		0.0f, 1.0f, 0.0f,	0.5f, 0.5f,
	//BR.x, BR.y, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 0.0f,
	//
	//BR.x, BR.y, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 0.0f,
	//BL.x, BL.y, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
	//TL.x, TL.y, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.5f

	TL.x, TL.y, 0.0f,	  1.0f, 0.0f, 0.0f,	  0.0f, 1.0f,
	TR.x, TR.y, 0.0f,	  0.0f, 1.0f, 0.0f,	  1.0f, 1.0f,
	BR.x, BR.y, 0.0f,	  0.0f, 0.0f, 1.0f,	  1.0f, 0.0f,
						  					  
	BR.x, BR.y, 0.0f,	  0.0f, 0.0f, 1.0f,	  1.0f, 0.0f,
	BL.x, BL.y, 0.0f,	  1.0f, 1.0f, 1.0f,	  0.0f, 0.0f,
	TL.x, TL.y, 0.0f,	  1.0f, 0.0f, 0.0f,	  0.0f, 1.0f
};
/*
float vertexBufferQuad[] = {
	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f
};
*/
unsigned int quadIndicesSprite[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

Sprite::Sprite(Renderer* _render) : Entity2D(_render, _boundsMin, _boundsMax) {
	renderer = _render;
	type = GL_QUADS;
	size = QUAD_VERTEX_BUFFER_SIZE;
	animation = NULL;

	for (int i = 0; i < QUAD_VERTEX_BUFFER_SIZE; i++)
	{
		vertexBuffer[i] = vertexBufferQuadSprite[i];
	}
}

Sprite::~Sprite()
{
	if (animation) delete animation;
}

TextureData Sprite::setTexture(const char* filePath, int _type)
{
	textureData = texture.importTexture(filePath, _type);
	type = _type;

	updateAnimation();

	return textureData;
}

void Sprite::loadTexture()
{
	texture.loadTexture(textureData, type);

	updateAnimation();
}

void Sprite::updateAnimation()
{
	if (animation)
	{
		animation->Update();
		Frame frame = animation->GetAnimation()[animation->GetCurrentFrame()];

		vertexBuffer[6] = frame.frameCoords[0].u;
		vertexBuffer[7] = frame.frameCoords[0].v;
		vertexBuffer[14] = frame.frameCoords[1].u;
		vertexBuffer[15] = frame.frameCoords[1].v;
		vertexBuffer[22] = frame.frameCoords[2].u;
		vertexBuffer[23] = frame.frameCoords[2].v;
		vertexBuffer[30] = frame.frameCoords[2].u;
		vertexBuffer[31] = frame.frameCoords[2].v;
		vertexBuffer[38] = frame.frameCoords[3].u;
		vertexBuffer[39] = frame.frameCoords[3].v;
		vertexBuffer[46] = frame.frameCoords[0].u;
		vertexBuffer[47] = frame.frameCoords[0].v;

		setBufferData();
	}
}

void Sprite::setBufferData() {
	renderer->setBufferData(size, vertexBuffer);
}

void Sprite::setAnimation(Animation* _animation)
{
	animation = _animation;
}

Animation* Sprite::getAnimation()
{
	return animation;
}