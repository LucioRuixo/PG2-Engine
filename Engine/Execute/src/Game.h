#ifndef GAME_H
#define GAME_H

#include <string>
#include "Gamebase/Gamebase.h"
#include "Entity/Cube/Cube.h"
#include "Entity/Plane/Sprite/Sprite.h"
#include "Entity/Model/Model.h"

using namespace std;

class Game : public GameBase
{
public:
	Game();
	~Game();
	int initialize() override;
	void update() override;
	int terminate() override;
};

#endif // !GAME_H