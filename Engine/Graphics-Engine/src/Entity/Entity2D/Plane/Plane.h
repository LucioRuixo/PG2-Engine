#ifndef PLANE_H
#define PLANE_H

#include "../../../Tools/Includes.h"
#include "../Entity2D.h"

const int PLANE_VERTEX_COMPONENTS = 66;

class GENGINE_API Plane : public Entity2D
{
private:
	const int vertexAmount = 6;

	static float vertices[PLANE_VERTEX_COMPONENTS];
public:
	Plane(Renderer* _renderer);
	~Plane();
	void draw();
};

#endif // !PLANE_H