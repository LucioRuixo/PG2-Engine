#ifndef CUBE_H
#define CUBE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int CUBE_VERTEX_COMPONENTS = 396;

class GENGINE_API Cube : public Entity
{
private:
	const int vertexAmount = 36;

	static float vertices[CUBE_VERTEX_COMPONENTS];
public:
	Cube(Renderer* _renderer);
	~Cube();
	void draw();
};

#endif // !CUBE_H