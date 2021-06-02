#include "Sprite.h"

using namespace glm;

Sprite::Sprite(Renderer* _renderer, TextureManager* _textureManager) : Plane(renderer)
{
	textureActive = true;

	renderer = _renderer;
	textureManager = _textureManager;
	animation = NULL;
}

Sprite::Sprite(Renderer * _renderer, TextureManager * _textureManager, const char* texturePath, int textureFormat, string textureName) : Plane(renderer)
{
	textureActive = true;

	renderer = _renderer;
	textureManager = _textureManager;
	animation = NULL;

	setTexture(texturePath, textureFormat, textureName);
}

Sprite::Sprite(Renderer* _renderer, TextureManager* _textureManager, vec3 _color) : Plane(_renderer, _color)
{
	textureActive = true;

	renderer = _renderer;
	textureManager = _textureManager;
	animation = NULL;
}

Sprite::Sprite(Renderer* _renderer, TextureManager* _textureManager, Material _material) : Plane(_renderer, _material)
{
	textureActive = true;

	renderer = _renderer;
	textureManager = _textureManager;
	animation = NULL;
}

Sprite::Sprite(Renderer* _renderer, TextureManager* _textureManager, vec3 _color, Material _material) : Plane(_renderer, _color, _material)
{
	textureActive = true;

	renderer = _renderer;
	textureManager = _textureManager;
	animation = NULL;
}

Sprite::~Sprite() { if (animation) delete animation; }

Texture Sprite::setTexture(const char* path, int format, string name)
{
	texture = textureManager->createTextureFromFile(path, format, name);

	updateAnimation();

	return texture;
}
Texture Sprite::getTexture() { return texture; }

void Sprite::setAnimation(Animation* _animation) { animation = _animation; }
Animation* Sprite::getAnimation() { return animation; }

void Sprite::updateAnimation()
{
	if (animation)
	{
		animation->update();
		Frame frame = animation->getAnimation()[animation->getCurrentFrame()];

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

		renderer->setVertexBufferData(PLANE_VERTEX_COMPONENTS, vertexBuffer);
	}
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture.id);
	Plane::draw();
}