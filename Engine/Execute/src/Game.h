#ifndef GAME_H
#define GAME_H

#include "Gamebase/Gamebase.h"
#include "Entity/Cube/Cube.h"
#include "Entity/Entity2D/Plane/Sprite/Sprite.h"

class Game : public GameBase
{
public:
	Game();
	~Game();
	int initialize();
	void update();
	int terminate();
};

#endif // !GAME_H