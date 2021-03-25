#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Tile.h"
#include "Renderer.h"

class GENGINE_API TileMap
{
	int width;
	int height;
	float tileWidth;
	float tileHeight;
	Tile** tiles;

public:
	TileMap(int _width, int _height, float _tileWidth, float _tileHeight, float initialX, float initialY, Sprite* baseSprite, Renderer* renderer);
	~TileMap();
	int getWidth();
	int getHeight();
	float getTileWidth();
	float getTileHeight();
	Tile* getTile(int x, int y);
	void draw(Renderer* renderer);
	void detectCollisions(Sprite* other);
};

#endif //!TILE_MAP_H