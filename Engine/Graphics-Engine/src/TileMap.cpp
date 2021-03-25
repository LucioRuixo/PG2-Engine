#include "TileMap.h"

TileMap::TileMap(int _width, int _height, float _tileWidth, float _tileHeight, float initialX, float initialY, Sprite* baseSprite, Renderer* renderer)
{
	width = _width;
	height = _height;
	tileWidth = _tileWidth;
	tileHeight = _tileHeight;
	tiles = new Tile*[width * height];

	for (int y = 0; y < height; y++)
	{
		float tileY = initialY + tileHeight * y;

		for (int x = 0; x < width; x++)
		{
			float tileX = initialX + tileWidth * x;

			tiles[y * width + x] = new Tile(tileX, tileY, tileWidth, tileHeight, baseSprite, renderer);
		}
	}
}

TileMap::~TileMap()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (tiles[y * width + x]) delete tiles[y * width + x];
		}
	}
}

int TileMap::getWidth()
{
	return width;
}

int TileMap::getHeight()
{
	return height;
}

float TileMap::getTileWidth()
{
	return tileWidth;
}

float TileMap::getTileHeight()
{
	return tileHeight;
}

Tile* TileMap::getTile(int x, int y)
{
	return tiles[y * width + x];
}

void TileMap::draw(Renderer* renderer)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile* tile = tiles[y * width + x];
			tile->draw();
		}
	}
}

void TileMap::detectCollisions(Sprite* other)
{
	//std::cout << "min x: " << tiles[0]->getBounds().min.x << " - min y: " << tiles[0]->getBounds().min.y << std::endl;
	//std::cout << "max x: " << tiles[0]->getBounds().max.x << " - max y: " << tiles[0]->getBounds().max.y << std::endl;
	//std::cout << "size x: " << tiles[0]->getBounds().size.x << " - size y: " << tiles[0]->getBounds().size.y << std::endl;

	bool collisionInX = false;
	bool collisionInY = false;
	int xCollisionTile = 0;
	int yCollisionTile = 0;

	float otherX = other->transform.position.x;
	float otherY = other->transform.position.y;

	for (int x = 0; x < width; x++)
	{
		Tile* tile = tiles[x];

		if (other->getBounds().min.x < tile->getBounds().max.x
			&&
			other->getBounds().max.x > tile->getBounds().min.x)
		{
			collisionInX = true;
			xCollisionTile = x;

			if (other->movingRight)
				otherX = tile->transform.position.x - tile->getBounds().size.x / 2.0f - other->getBounds().size.x / 2.0f;
			
			if (other->movingLeft)
			{
				xCollisionTile = x - 1;
				otherX = tile->transform.position.x - tile->getBounds().size.x / 2.0f + other->getBounds().size.x / 2.0f;
			}
		}
	}

	for (int y = 0; y < height; y++)
	{
		Tile* tile = tiles[y * width];

		if (other->getBounds().min.y < tile->getBounds().max.y
			&&
			other->getBounds().max.y > tile->getBounds().min.y)
		{
			collisionInY = true;
			yCollisionTile = y;

			if (other->movingUp)
				otherY = tile->transform.position.y - tile->getBounds().size.y / 2.0f - other->getBounds().size.y / 2.0f;
			
			if (other->movingDown)
			{
				yCollisionTile = y - 1;
				otherY = tile->transform.position.y - tile->getBounds().size.y / 2.0f + other->getBounds().size.y / 2.0f;
			}
		}
	}

	if ((collisionInX && collisionInY) && !tiles[yCollisionTile * width + xCollisionTile]->getWalkability())
	{
		std::cout << "COLISION" << std::endl;
		other->SetPosition(otherX, otherY, 0.0f);
	}
}