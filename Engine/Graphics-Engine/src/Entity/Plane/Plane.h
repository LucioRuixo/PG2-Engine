#ifndef PLANE_H
#define PLANE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int PLANE_VERTEX_COMPONENTS = 48;
const int PLANE_VERTICES = 6;

const int PLANE_INDEXED_VERTEX_COMPONENTS = 32;
const int PLANE_INDICES = 6;

class GENGINE_API Plane : public Entity
{
	static float vertices[PLANE_VERTEX_COMPONENTS];

	static float indexedVertices[PLANE_INDEXED_VERTEX_COMPONENTS];
	static unsigned int indices[PLANE_INDICES];
public:
	Plane(Renderer* _renderer);
	Plane(Renderer* _renderer, vec3 _color);
	Plane(Renderer* _renderer, Material _material);
	Plane(Renderer* _renderer, vec3 _color, Material _material);
	~Plane();

	void draw();
};

#endif // !PLANE_H