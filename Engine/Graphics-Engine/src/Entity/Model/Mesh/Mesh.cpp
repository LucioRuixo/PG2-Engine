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

void Mesh::draw(mat4 model)
{
	unsigned int uniformLocation = 0;

	////Texture
	//uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "spriteTextureActive");
	//glUniform1i(uniformLocation, 0);
	//
	////Color
	//uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "color");
	//glUniform3f(uniformLocation, 1.0f, 1.0f, 1.0f);
	//
	////Material
	//uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuseTexturesActive");
	//glUniform1i(uniformLocation, 1);
	//
	//uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specularTexturesActive");
	//glUniform1i(uniformLocation, 1);

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
				glActiveTexture(GL_TEXTURE1 + diffuseNumber);
				number = to_string(diffuseNumber++);
			}
		}
		else if (name == "specularTexture")
		{
			if (specularNumber >= MAX_TEXTURE_AMOUNT_PER_TYPE) continue;
			else
			{
				glActiveTexture(GL_TEXTURE5 + specularNumber);
				number = to_string(specularNumber++);
			}
		}

		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	setUniformValues();
	renderer->setModel(renderer->getShaderProgram(ShaderType::Main), model);
	renderer->drawElements(vao, vbo, ebo, indices.size());

	for (int i = 0; i < MAX_TEXTURE_AMOUNT_PER_TYPE * 2; i++)
	{
		glActiveTexture(GL_TEXTURE1 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}