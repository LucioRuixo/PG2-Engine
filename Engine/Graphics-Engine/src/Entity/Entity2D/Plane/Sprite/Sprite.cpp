#include "Sprite.h"

using namespace glm;

Sprite::Sprite(Renderer* _renderer) : Plane(renderer)
{
	renderer = _renderer;
	type = GL_QUADS;
	animation = NULL;
}

Sprite::~Sprite() { if (animation) delete animation; }

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

void Sprite::setAnimation(Animation* _animation) { animation = _animation; }

Animation* Sprite::getAnimation() { return animation; }

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

		//setBufferData();
		renderer->setBufferData(PLANE_VERTEX_COMPONENTS, vertexBuffer);
	}
}