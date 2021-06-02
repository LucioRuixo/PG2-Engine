#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Tools/Includes.h"
#include "TextureManager/TextureManager.h"

using namespace std;
using namespace glm;

struct Vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoordinates;
};

class GENGINE_API Mesh
{
	unsigned int vao, vbo, ebo;

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	void setupMesh();
public:
	Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures);

	vector<Vertex> getVertices();
	vector<unsigned int> getIndices();
	vector<Texture> getTextures();

	void draw();
};

#endif // !MESH_H