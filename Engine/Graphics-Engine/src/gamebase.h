#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "Includes.h"
#include "Renderer.h"
#include "Shape.h"
#include "Sprite.h"
#include "Window.h"
#include "Camera.h"
#include "Lighting.h"
#include "Input.h"
#include "TileMap.h"

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