#include "Tile.h"

Tile::Tile(float _x, float _y, float _width, float _height, Sprite* _sprite, Renderer* renderer) : Entity(/*renderer*/)
{
	//setPosition(_x, _y, 0.0f);
	//setScale(_width, _height, 0.0f);
	//bounds.size.x = _width;
	//bounds.size.y = _height;
	sprite = _sprite;

	walkable = true;
}

Tile::~Tile() {}

void Tile::setWalkability(bool _walkable)
{
	walkable = _walkable;
}

bool Tile::getWalkability()
{
	return walkable;
}

void Tile::setSprite(Sprite* _sprite)
{
	sprite = _sprite;
}

Sprite* Tile::getSprite()
{
	return sprite;
}

//(no funciona)
void Tile::draw()
{
	//sprite->loadTexture();
	//renderer->setModel(renderer->getShaderProgram(ShaderType::Main), getModel());
	//renderer->drawTriangles();
}