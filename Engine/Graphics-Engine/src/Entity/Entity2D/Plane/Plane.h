#ifndef PLANE_H
#define PLANE_H

#include "../../../Tools/Includes.h"
#include "../Entity2D.h"

const int PLANE_VERTEX_COMPONENTS = 48;

class GENGINE_API Plane : public Entity2D
{
private:
	static float vertices[PLANE_VERTEX_COMPONENTS];
public:
	Plane(Renderer* _renderer/*, int _type*/);
	~Plane();
};

#endif // !PLANE_H