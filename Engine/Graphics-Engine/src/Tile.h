#ifndef TILE_H
#define TILE_H

#include "Entity2D.h"
#include "Sprite.h"

class GENGINE_API Tile : public Entity2D
{
	bool walkable;
	Sprite* sprite;

public:
	Tile(float _x, float _y, float _width, float _height, Sprite* _sprite, Renderer* renderer);
	~Tile();
	void setWalkability(bool _walkable);
	bool getWalkability();
	void setSprite(Sprite* _sprite);
	Sprite* getSprite();
	void draw();
};

#endif //!TILE_H