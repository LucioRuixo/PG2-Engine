#include "Mesh.h"

Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures)
{
	vertices = _vertices;
	indices = _indices;
	textures = _textures;

	setupMesh();
}

void Mesh::setupMesh() {}

vector<Vertex> Mesh::getVertices() { return vector<Vertex>(); }

vector<unsigned int> Mesh::getIndices() { return vector<unsigned int>(); }

vector<Texture> Mesh::getTextures() { return vector<Texture>(); }

void Mesh::draw() {}