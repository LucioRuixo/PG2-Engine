#ifndef LIGHT_CUBE_H
#define LIGHT_CUBE_H

#include "Tools/Includes.h"
#include "../Cube.h"

class GENGINE_API LightCube : public Cube
{
public:
	LightCube();
	~LightCube();
	void draw() override;
};

#endif // !LIGHT_CUBE_H