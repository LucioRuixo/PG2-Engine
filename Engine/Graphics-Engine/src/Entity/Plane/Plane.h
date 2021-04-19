#ifndef PLANE_H
#define PLANE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int PLANE_VERTEX_COMPONENTS = /*66*/48;

class GENGINE_API Plane : public Entity
{
	static float vertices[PLANE_VERTEX_COMPONENTS];
protected:
	const int vertexAmount = 6;
public:
	Plane(Renderer* _renderer);
	Plane(Renderer* _renderer, vec3 _color);
	Plane(Renderer* _renderer, Material _material);
	Plane(Renderer* _renderer, vec3 _color, Material _material);
	~Plane();
	virtual void draw();
};

#endif // !PLANE_H