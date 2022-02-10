#ifndef PLANE_H
#define PLANE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int PLANE_VERTEX_COMPONENTS = 32;
const int PLANE_INDICES = 6;
const int PLANE_VERTICES = 4;

class GENGINE_API Plane : public Entity
{
	static unsigned int vao;
	static unsigned int vbo;
	static unsigned int ebo;

	static float vertices[PLANE_VERTEX_COMPONENTS];
	static unsigned int indices[PLANE_INDICES];

public:
	static void initializeRenderingData();

	Plane(bool renderizable = true);
	Plane(vec3 _color, bool renderizable = true);
	Plane(Material _material, bool renderizable = true);
	Plane(vec3 _color, Material _material, bool renderizable = true);
	~Plane();

	vec3 getNormal();

	float distanceToPoint(vec3 point);
	bool sameSide(vec3 a, vec3 b);
	bool sameSide(vec3 a, vector<vec3> b);

#pragma Collision Box
	vector<vec3> getCollisionBoxVertices() override;
#pragma endregion

	virtual void draw() override;
};

#endif // !PLANE_H