#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <assimp/Importer.hpp>
#include "Tools/Includes.h"
#include "Camera/Camera.h"
#include "Input/Input.h"
#include "Lighting/Lighting.h"
#include "Renderer/Renderer.h"
#include "TextureManager/TextureManager.h"
#include "TileMap/TileMap.h"
#include "Time/Time.h"
#include "Window/Window.h"

class GENGINE_API GameBase
{
protected:
	Window* window;
	Renderer* renderer;
	Camera* camera;
	TextureManager* textureManager;
	Lighting* lighting;
	Input* input;
	Time* time;

	Assimp::Importer importer;
	
public:
	GameBase();
	~GameBase();
	void run();
	virtual int initialize() = 0;
	virtual void update() = 0;
	virtual int terminate() = 0;
};

#endif // !GAMEBASE_H