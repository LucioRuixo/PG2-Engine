#ifndef CUBE_H
#define CUBE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int CUBE_VERTEX_COMPONENTS = /*396*/288;

class GENGINE_API Cube : public Entity
{
protected:
	const int vertexAmount = 36;
	static float vertices[CUBE_VERTEX_COMPONENTS];
public:
	Cube(Renderer* _renderer);
	Cube(Renderer* _renderer, vec3 _color);
	Cube(Renderer* _renderer, Material _material);
	Cube(Renderer* _renderer, vec3 _color, Material _material);
	~Cube();
	virtual void draw();
};

#endif // !CUBE_H