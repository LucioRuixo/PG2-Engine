#include "Mesh.h"

Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures) : Entity()
{
	vertices = _vertices;
	indices = _indices;
	textures = _textures;

	setupMesh();
}

Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures, Material _material) : Entity(_material)
{
	vertices = _vertices;
	indices = _indices;
	textures = _textures;

	setupMesh();
}

Mesh::~Mesh()
{
	if (!vertices.empty()) vertices.clear();
	if (!indices.empty()) indices.clear();
	if (!textures.empty()) textures.clear();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	//Texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoordinates));

	glBindVertexArray(0);
}

vector<Vertex> Mesh::getVertices() { return vertices; }

vector<unsigned int> Mesh::getIndices() { return indices; }

vector<Texture> Mesh::getTextures() { return textures; }

#pragma region Collision Box
vector<vec3> Mesh::getCollisionVertices()
{
	cout << "Can not generate collision vertices for this class (Mesh)" << endl;
	return vector<vec3>();
}
#pragma endregion

void Mesh::draw(/*mat4 model /*Renderer* renderer, TextureManager* textureManager*/)
{
	unsigned int uniformLocation = 0;

	unsigned int diffuseNumber = 0;
	unsigned int specularNumber = 0;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		string number;
		string name = textures[i].type;

		if (name == "diffuseTexture")
		{
			if (diffuseNumber >= MAX_TEXTURE_AMOUNT_PER_TYPE) continue;
			else
			{
				textureManager->setActiveTextureUnit(1 + diffuseNumber);
				number = to_string(diffuseNumber++);
			}
		}
		else if (name == "specularTexture")
		{
			if (specularNumber >= MAX_TEXTURE_AMOUNT_PER_TYPE) continue;
			else
			{
				textureManager->setActiveTextureUnit(5 + specularNumber);
				number = to_string(specularNumber++);
			}
		}

		textureManager->bind2DTexture(textures[i].id);
	}
	textureManager->setActiveTextureUnit(0);

	setUniformValues();
	//renderer->setModel(renderer->getShaderProgram(shader), transform->getModel());
	renderer->drawElements(vao, vbo, ebo, indices.size());

	for (int i = 0; i < MAX_TEXTURE_AMOUNT_PER_TYPE * 2; i++)
	{
		textureManager->setActiveTextureUnit(1 + i);
		textureManager->bind2DTexture(0);
	}

	Entity::draw();
}