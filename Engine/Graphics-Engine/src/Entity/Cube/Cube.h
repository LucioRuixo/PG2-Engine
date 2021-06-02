#ifndef CUBE_H
#define CUBE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int CUBE_VERTEX_COMPONENTS = 288;
const int CUBE_VERTICES = 36;

const int CUBE_INDEXED_VERTEX_COMPONENTS = 288;
const int CUBE_INDICES = 36;

class GENGINE_API Cube : public Entity
{
protected:
	static float vertices[CUBE_VERTEX_COMPONENTS];

	//static float indexedVertices[CUBE_INDEXED_VERTEX_COMPONENTS];
	static unsigned int indices[CUBE_INDICES];
public:
	Cube(Renderer* _renderer);
	Cube(Renderer* _renderer, vec3 _color);
	Cube(Renderer* _renderer, Material _material);
	Cube(Renderer* _renderer, vec3 _color, Material _material);
	~Cube();

	virtual void draw();
};

#endif // !CUBE_H