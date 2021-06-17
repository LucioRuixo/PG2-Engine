#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "TextureManager/TextureManager.h"

using namespace std;
using namespace glm;

struct Vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoordinates;
};

const int MAX_TEXTURE_AMOUNT_PER_TYPE = 4;

class GENGINE_API Mesh
{
	unsigned int vao, vbo, ebo;

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Renderer* renderer;

	void setupMesh();
public:
	Mesh(Renderer* _renderer, vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures);
	~Mesh();

	vector<Vertex> getVertices();
	vector<unsigned int> getIndices();
	vector<Texture> getTextures();

	void draw(mat4 model);
};

#endif // !MESH_H