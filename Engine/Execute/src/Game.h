#ifndef GAME_H
#define GAME_H
#include "Gamebase.h"

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