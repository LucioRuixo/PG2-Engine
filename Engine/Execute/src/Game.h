#ifndef GAME_H
#define GAME_H

#include <string>
#include "Gamebase/Gamebase.h"
#include "Entity/Cube/Cube.h"
#include "Entity/Plane/Sprite/Sprite.h"

using namespace std;

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