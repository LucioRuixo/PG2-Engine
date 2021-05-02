#ifndef LIGHT_CUBE_H
#define LIGHT_CUBE_H

#include "Tools/Includes.h"
#include "../Cube.h"

class GENGINE_API LightCube : public Cube
{
public:
	LightCube(Renderer* _renderer);
	~LightCube();
	void draw();
};

#endif // !LIGHT_CUBE_H