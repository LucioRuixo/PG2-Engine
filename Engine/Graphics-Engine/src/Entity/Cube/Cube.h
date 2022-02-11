#ifndef CUBE_H
#define CUBE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int CUBE_VERTEX_COMPONENTS = 288;
const int CUBE_INDICES = 36;
const int CUBE_VERTICES = 8;

class GENGINE_API Cube : public Entity
{
	static int collisionVertexIndices[CUBE_VERTICES];

protected:
	static unsigned int vao;
	static unsigned int vbo;
	static unsigned int ebo;

	static float vertices[CUBE_VERTEX_COMPONENTS];
	static unsigned int indices[CUBE_INDICES];
public:
	static void initializeRenderingData();

	Cube(bool renderizable = true);
	Cube(vec3 _color, bool renderizable = true);
	Cube(Material _material, bool renderizable = true);
	Cube(vec3 _color, Material _material, bool renderizable = true);
	~Cube();

#pragma Collision Box
	vector<vec3> getCollisionVertices() override;
#pragma endregion

	virtual void draw() override;
};

#endif // !CUBE_H