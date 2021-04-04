#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "../Tools/Includes.h"
#include "../Camera/Camera.h"
#include "../Entity/Entity2D/Plane/Plane.h"
#include "../Entity/Entity2D/Plane/Sprite/Sprite.h"
#include "../Input/Input.h"
#include "../Lighting/Lighting.h"
#include "../Renderer/Renderer.h"
#include "../TileMap/TileMap.h"
#include "../Time/Time.h"
#include "../Window/Window.h"

class GENGINE_API GameBase
{
protected:
	float translationX;
	float translationY;
	float translationZ;
	float rotateX;
	float rotateY;
	float rotateZ;
	float scaleX;
	float scaleY;
	float scaleZ;

	Window* window;
	Renderer* renderer;
	Camera* camera;
	Lighting* lighting;
	Input* input;
	Time* time;
public:
	GameBase();
	~GameBase();
	void run();
	virtual int initialize() = 0;
	virtual void update() = 0;
	virtual int terminate() = 0;
};

#endif // !GAMEBASE_H