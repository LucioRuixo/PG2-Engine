#ifndef CUBE_H
#define CUBE_H

#include "Tools/Includes.h"
#include "../Entity.h"

const int CUBE_VERTEX_COMPONENTS = 288;
const int CUBE_INDICES = 36;

class GENGINE_API Cube : public Entity
{
protected:
	static unsigned int vao;
	static unsigned int vbo;
	static unsigned int ebo;

	static float vertices[CUBE_VERTEX_COMPONENTS];
	static unsigned int indices[CUBE_INDICES];
public:
	static void initializeRenderingObjects();

	Cube();
	Cube(vec3 _color);
	Cube(Material _material);
	Cube(vec3 _color, Material _material);
	~Cube();

	virtual void draw() override;
};

#endif // !CUBE_H