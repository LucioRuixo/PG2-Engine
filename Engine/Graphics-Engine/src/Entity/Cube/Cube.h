#ifndef CUBE_H
#define CUBE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int CUBE_VERTEX_COMPONENTS = 288;
//const int CUBE_VERTEX_POSITIONS_COMPONENTS = 24;
const int CUBE_INDICES = 36;

class GENGINE_API Cube : public Entity
{
protected:
	static unsigned int vao;
	static unsigned int vbo;
	static unsigned int ebo;

	static float vertices[CUBE_VERTEX_COMPONENTS];
	//static float vertexPositions[CUBE_VERTEX_POSITIONS_COMPONENTS];
	static unsigned int indices[CUBE_INDICES];
public:
	static void initializeRenderingData();

	Cube(bool renderizable = true);
	Cube(vec3 _color, bool renderizable = true);
	Cube(Material _material, bool renderizable = true);
	Cube(vec3 _color, Material _material, bool renderizable = true);
	~Cube();

	//vec3* getVertices();

#pragma Collision Box
	vector<vec3> getCollisionBoxVertices() override;
#pragma endregion

	virtual void draw() override;
};

#endif // !CUBE_H